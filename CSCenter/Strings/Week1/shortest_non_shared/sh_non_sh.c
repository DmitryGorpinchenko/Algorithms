#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 6

typedef struct Node {
    int d, s, e, pos;
    struct Node* p;
    struct Node* nxt[ALPHA_SIZE];
} Node;

typedef struct SuffixTree {
    Node* root;
    char* text;
} SuffixTree;

char* sh_non_sh(char* txt1, int size1, char* txt2, int size2); 
SuffixTree* suff_tree(char* text, int* suff, int* lcp, int size);
int find_sh_non_sh(Node* n, int size1, Node** ptr, int* curr_min, char* txt);
void free_suff_tree(SuffixTree** st);
int match(SuffixTree* st, char* pattern);
Node* split(Node* ptr, char* text, int s, int offset);
Node* node(Node* p, int d, int s, int e, int pos);
void print_suff_tree(SuffixTree* st);
void print_node_rec(Node* n, char* text);
void free_node(Node* n);
int* suff_arr(char* text, int size);
int* sort_characters(char* text, int size);
int* compute_char_classes(char* text, int* order, int size);
int* sort_doubled(char* text, int L, int* order, int* cl, int size);
int* update_classes(int* order, int* cl, int L, int size);
int* inv_suff_arr(int* order, int size);
int* lcp_arr(char* text, int* order, int size);
char* inv_bwt(char* bwt, int size);
int to_digit(char c);

int main() {
    size_t size1, size2, tmp;
    char *txt1 = NULL, *txt2 = NULL;
    getline(&txt1, &tmp, stdin);
    txt1[size1 = strlen(txt1) - 1] = 0;
    getline(&txt2, &tmp, stdin);
    txt2[(size2 = strlen(txt2)) - 1] = '$';
    char* sh_n_sh = sh_non_sh(txt1, size1, txt2, size2);
    printf("%s\n", sh_n_sh);
    free(txt1);
    free(txt2);
    free(sh_n_sh);
    return 0;
}

char* sh_non_sh(char* txt1, int size1, char* txt2, int size2) {
    int size = size1 + 1 + size2;
    char* txt = calloc(size + 1, sizeof(char));
    int i = 0;
    for(; i < size1; i++) {
        txt[i] = txt1[i];
    }
    txt[i++] = '#';
    for(; i < size; i++) {
        txt[i] = txt2[i - size1 - 1];
    }
    int* suff = suff_arr(txt, size);
    int* lcp = lcp_arr(txt, suff, size);
    SuffixTree* st = suff_tree(txt, suff, lcp, size);
    free(suff); free(lcp);
    Node* ptr;
    int curr_min = size1;
    find_sh_non_sh(st->root, size1, &ptr, &curr_min, txt);
    char* sh_n_sh = calloc(curr_min + 1, sizeof(char));
    i = curr_min - 1;
    while(ptr->p) {
        char* tmp = txt + (ptr->pos == -1 ? ptr->e - 1 : ptr->s);
        while(tmp != txt + ptr->s - 1) {
            sh_n_sh[i--] = *tmp--; 
        }
        ptr = ptr->p;
    } 
    free_suff_tree(&st);
    free(txt);
    return sh_n_sh;
}

int find_sh_non_sh(Node* n, int size1, Node** ptr, int* curr_min, char* txt) {
    int is_cand = n->pos != -1 ? n->s < size1 + 1 : 1;
    for(int i = 0; i < ALPHA_SIZE; i++) {
        if(n->nxt[i]) {
	    //it is essential to put 'is_cand' second due to the '&&' operator semantics
            is_cand = find_sh_non_sh(n->nxt[i], size1, ptr, curr_min, txt) && is_cand;
        }
    }
    int depth = n->pos == -1 ? n->d : n->p->d + 1;
    if(is_cand && *curr_min >= depth && txt[n->s] != '#')  {
        *ptr = n;
        *curr_min = depth;
    }
    return is_cand;
}

SuffixTree* suff_tree(char* text, int* suff, int* lcp, int size) {
    SuffixTree* st = malloc(sizeof(SuffixTree));
    st->text = text;
    st->root = node(NULL, 0, -1, -1, -1);
    Node* ptr = st->root;
    int id, prev = 0;
    for(int i = 0; i < size; i++) {
        while(ptr->d > prev && (ptr = ptr->p));
        ptr = ptr->d != prev ? split(ptr, text, suff[i - 1] + ptr->d, prev - ptr->d) : ptr;
        id = to_digit(text[suff[i] + ptr->d]);
        ptr = ptr->nxt[id] = node(ptr, size - suff[i], suff[i] + ptr->d, size, suff[i]);
        prev = lcp[i < size - 1 ? i : 0];
    }
    return st;
}

int match(SuffixTree* st, char* pattern) {
    Node* cur = st->root;
    while(*pattern && (cur = cur->nxt[to_digit(*pattern)])) {
        char* tmp = st->text + cur->s;
        while(tmp != st->text + cur->e && *pattern && (*pattern == *tmp)) {
            pattern++; tmp++;
        }
        if(tmp != st->text + cur->e && *pattern) {
            cur = NULL;
            break;
        }
    }
    return cur != NULL;   
}

Node* split(Node* ptr, char* text, int s, int o) {
    int start = to_digit(text[s]), mid = to_digit(text[s + o]);
    Node* mid_node = node(ptr, ptr->d + o, s, s + o, -1);
    mid_node->nxt[mid] = ptr->nxt[start];
    ptr->nxt[start]->s += o;
    ptr->nxt[start]->p = mid_node; ptr->nxt[start] = mid_node;
    return mid_node;
}

Node* node(Node* p, int d, int s, int e, int pos) {
    Node* n = calloc(1, sizeof(Node)); //inits nxt to NULLs 
    n->p = p; n->d = d; n->pos = pos;
    n->s = s; n->e = e;
    return n;
}

void print_suff_tree(SuffixTree* st) {
    print_node_rec(st->root, st->text);
}

void print_node_rec(Node* n, char* text) {
    for(int i = 0; i < ALPHA_SIZE; i++) {
        if(n->nxt[i]) {
            printf("%.*s %d\n", n->nxt[i]->e - n->nxt[i]->s, text + n->nxt[i]->s, n->nxt[i]->p == n);
            print_node_rec(n->nxt[i], text);
        }       
    }
}

void free_suff_tree(SuffixTree** st) {
    free_node((*st)->root);
    free(*st);
    *st = NULL;
}

void free_node(Node* n) {
    if(n == NULL) {
        return;
    }
    for(int i = 0; i < ALPHA_SIZE; i++) {
        free_node(n->nxt[i]);
    }
    free(n);
}

int* suff_arr(char* text, int size) {
    int* order = sort_characters(text, size);
    int* cl = compute_char_classes(text, order, size);
    int L = 1;
    while(L < size) {
        order = sort_doubled(text, L, order, cl, size);
        cl = update_classes(order, cl, L, size);
        L *= 2;
    }
    free(cl);
    return order;
}

int* sort_characters(char* text, int size) {
    int* order = malloc(sizeof(int) * size);
    int* count = calloc(ALPHA_SIZE, sizeof(int));
    for(int i = 0; i < size; i++) {
        ++count[to_digit(text[i])];
    }
    for(int i = 1; i < ALPHA_SIZE; i++) {
        count[i] += count[i - 1];
    }
    for(int i = size - 1; i >= 0; i--) {
        order[--count[to_digit(text[i])]] = i;
    }
    free(count);
    return order;
}

int* compute_char_classes(char* text, int* order, int size) {
    int* cl = calloc(size, sizeof(int));
    for(int i = 1; i < size; i++) {
        cl[order[i]] = cl[order[i - 1]] + (text[order[i]] != text[order[i - 1]]);
    }
    return cl;
}

int* sort_doubled(char* text, int L, int* order, int* cl, int size) {
    int* count = calloc(size, sizeof(int));
    int* new_order = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        ++count[cl[i]];
    }
    for(int i = 1; i < size; i++) {
        count[i] += count[i - 1];
    }
    for(int i = size - 1; i >= 0; i--) {
        int start = (order[i] - L + size) % size;
        new_order[--count[cl[start]]] = start;
    }
    free(order);
    free(count);
    return new_order;
}

int* update_classes(int* order, int* cl, int L, int size) {
    int cur, prev, mid, mid_prev;
    int* new_cl = calloc(size, sizeof(int));
    for(int i = 1; i < size; i++) {
        cur = order[i]; prev = order[i - 1];
        mid = (cur + L) % size; mid_prev = (prev + L) % size;
        new_cl[cur] = new_cl[prev] + (cl[cur] != cl[prev] || cl[mid] != cl[mid_prev]);
    }
    free(cl);
    return new_cl;
}

int* inv_suff_arr(int* order, int size) {
    int* pos = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        pos[order[i]] = i;
    }
    return pos;
}

int* lcp_arr(char* text, int* order, int size) {
    int* lcp_array = malloc(sizeof(int) * (size - 1));
    int k = 0;
    int* pos = inv_suff_arr(order, size);
    for(int i = 0; i < size; i++, k ? k-- : 0) {
        if(pos[i] == size - 1) {
            k = 0;
            continue;
        }
        int j = order[pos[i] + 1];
        while(i + k < size && j + k < size && text[i + k] == text[j + k]) {
            k++;
        }
        lcp_array[pos[i]] = k;
    }
    free(pos);
    return lcp_array;
}

char* inv_bwt(char* bwt, int size) {
    int* tmp = calloc(ALPHA_SIZE + 1, sizeof(int));
    for(int i = 0; i < size; i++) {
        tmp[to_digit(bwt[i]) + 1]++;
    }    
    for(int i = 1; i < ALPHA_SIZE; i++) {
        tmp[i + 1] += tmp[i];
    }
    int* map = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        map[i] = tmp[to_digit(bwt[i])]++;
    }
    char* text = calloc(size + 1, sizeof(char));
    int ptr = 0, back_ptr = size - 1; text[back_ptr] = '$';
    while(bwt[ptr] != '$') {
        text[--back_ptr] = bwt[ptr];
        ptr = map[ptr];
    }
    free(tmp);
    free(map);
    return text;
}

int to_digit(char c) {
    switch(c) {
        case '#' : return  0;
        case '$' : return  1;
        case 'A' : return  2;
        case 'C' : return  3;
        case 'G' : return  4;
        case 'T' : return  5;
        default  : return -1;
    }
}
