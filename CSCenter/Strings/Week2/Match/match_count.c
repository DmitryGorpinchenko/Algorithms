#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 5

typedef struct Node {
    int d, s, e, pos, leaves;
    struct Node* p;
    struct Node* nxt[ALPHA_SIZE];
} Node;

typedef struct SuffixTree {
    Node* root;
    char* text;
} SuffixTree;

SuffixTree* suff_tree(char* text, int* suff, int* lcp, int size);
void free_suff_tree(SuffixTree** st);
int match_count(SuffixTree* st, char* pattern);
int count_leaves(Node* subtree);
Node* split(Node* ptr, char* text, int s, int offset);
Node* node(Node* p, int d, int s, int e, int pos);
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
    size_t size, tmp;
    char *bwt = NULL, *buff = NULL;
    getline(&bwt, &tmp, stdin);
    bwt[size = strlen(bwt) - 1] = 0;
    getline(&buff, &tmp, stdin);
    int n = atoi(buff);
    char* patterns = NULL;
    getline(&patterns, &tmp, stdin);
    int patterns_size = strlen(patterns);
    //preprocess to have null-terminators instead of spaces between patterns
    for(int i = 0; i < patterns_size; i++) {
        if(patterns[i] == ' ' || patterns[i] == '\n') {
            patterns[i] = 0;
        }
    }
    char* text = inv_bwt(bwt, size);
    int* suff = suff_arr(text, size);
    int* lcp = lcp_arr(text, suff, size);
    SuffixTree* st = suff_tree(text, suff, lcp, size);
    char* pattern = patterns;
    for(int i = 0; i < n; i++) {
        printf("%d ", match_count(st, pattern));
        pattern += strlen(pattern) + 1;
    }
    printf("\n");
    free(bwt);
    free(patterns);
    free(buff);
    free(text);
    free(suff);
    free(lcp);
    free_suff_tree(&st);
    return 0;
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
    st->root->leaves = count_leaves(st->root);
    return st;
}

int match_count(SuffixTree* st, char* pattern) {
    Node* cur = st->root;
    while(*pattern && (cur = cur->nxt[to_digit(*pattern)])) {
        char* tmp = st->text + cur->s;
        while(tmp != st->text + cur->e && *pattern && *pattern == *tmp) {
            pattern++; tmp++;
        }
        if(tmp != st->text + cur->e && *pattern) {
            cur = NULL;
            break;
        }
    }
    return cur ? cur->leaves : 0;   
}

int count_leaves(Node* subtree) {
    if(subtree->pos != -1) {
        return 1;
    }
    int leaves = 0;
    for(int i = 0; i < ALPHA_SIZE; i++) {
        if(subtree->nxt[i]) {
            leaves += (subtree->nxt[i]->leaves = count_leaves(subtree->nxt[i]));
        } 
    }
    return leaves;
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
        case '$' : return  0;
        case 'A' : return  1;
        case 'C' : return  2;
        case 'G' : return  3;
        case 'T' : return  4;
        default  : return -1;
    }
}