#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 5

typedef struct Node {
    int d, s, e, pos;
    struct Node* p;
    struct Node* nxt[ALPHA_SIZE];
} Node;

typedef struct SuffixTree {
    Node* root;
    char* text;
} SuffixTree;

SuffixTree* suff_tree(char* text, int* suff, int* lcp, int size);
void free_suff_tree(SuffixTree** st);
Node* split(Node* ptr, char* text, int s, int offset);
Node* node(Node* p, int d, int s, int e, int pos);
void free_node(Node* n);
void print_suff_tree(SuffixTree* st);
void print_node_rec(Node* n);
int to_digit(char c);

int main() {
    size_t size, tmp;
    char* text = NULL;
    getline(&text, &tmp, stdin);
    text[size = strlen(text) - 1] = 0; //strip off new line
    int* suff_arr = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++) {
        scanf("%d", suff_arr + i); //it seems safe to use scanf after getline
    }    
    int* lcp = malloc(sizeof(int) * (size - 1));
    for(int i = 0; i < size - 1; i++) {
        scanf("%d", lcp + i); //it seems safe to use scanf after getline
    }
    SuffixTree* st = suff_tree(text, suff_arr, lcp, size);
    print_suff_tree(st);
    free(text);
    free(suff_arr);
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
    return st;
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
    printf("%s\n", st->text);
    print_node_rec(st->root);
}

void print_node_rec(Node* n) {
    for(int i = 0; i < ALPHA_SIZE; i++) {
        if(n->nxt[i]) {
            printf("%d %d\n", n->nxt[i]->s, n->nxt[i]->e);
            print_node_rec(n->nxt[i]);
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
