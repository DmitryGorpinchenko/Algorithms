#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 4

typedef struct Trie {
    int is_pattern;
    struct Trie* next[ALPHA_SIZE];
} Trie;

int match(Trie* tr, char* txt);
void add_string(Trie* tr, char* str, int size);
void free_trie(Trie** tr);
int to_digit(char c);

int main() {
    char *txt = NULL, *buffer = NULL;
    size_t size;
    getline(&txt, &size, stdin);
    getline(&buffer, &size, stdin);
    size_t n = atoi(buffer);
    Trie* tr = calloc(1, sizeof(Trie)); //simulate init to zero
    for(int i = 0; i < n; i++) {
        getline(&buffer, &size, stdin);
	    add_string(tr, buffer, strlen(buffer) - 1); //exclude new line
    }
    n = strlen(txt) - 1; //exclude new line
    for(int i = 0; i < n; i++) {
        if(match(tr, txt + i)) {
            printf("%d ", i);
        }
    }
    printf("\n");
    free_trie(&tr);
    free(txt);
    free(buffer);
    return 0;
}

int match(Trie* tr, char* txt) {
    while(*txt && (tr = tr->next[to_digit(*txt++)]) && !tr->is_pattern);
    return tr ? tr->is_pattern : 0;
}

void add_string(Trie* tr, char* str, int size) {
    for(int i = 0; i < size; i++) {
	    Trie* tmp = tr->next[to_digit(str[i])];    
	    tr = tmp ? tmp : (tr->next[to_digit(str[i])] = calloc(1, sizeof(Trie))); 
    }
    tr->is_pattern = 1;
}

void free_trie(Trie** tr) {
    if(*tr == NULL) {
        return;
    }
    for(int i = 0; i < ALPHA_SIZE; i++) {
        free_trie(&(*tr)->next[i]);
    }
    free(*tr);
    *tr = NULL;
}

int to_digit(char c) {
    switch(c) {
        case 'A' : return  0; 
        case 'C' : return  1;
        case 'G' : return  2;
        case 'T' : return  3;
	    default  : return -1;
    }
}
