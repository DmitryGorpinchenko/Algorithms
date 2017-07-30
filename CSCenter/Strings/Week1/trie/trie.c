#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA_SIZE 4

typedef struct Trie {
    struct Trie* next[ALPHA_SIZE];
} Trie;

Trie* new_trie();
void add_string(Trie* trie, char* str);
void print_trie(Trie* trie);
void print_trie_rec(Trie* trie, int parent, int* count); 
void delete_trie(Trie** trie);
int to_digit(char c);
char to_letter(int d);

int main() {
    size_t n, size;
    char* buffer = NULL;
    getline(&buffer, &size, stdin);
    buffer[strlen(buffer) - 1] = 0;
    n = atoi(buffer);
    char* patterns[n];
    for(int i = 0; i < n; i++) {
        getline(&buffer, &size, stdin);
        size = strlen(buffer);
        buffer[size - 1] = 0; //strip the new line character 
        patterns[i] = malloc(sizeof(char) * size);
        strcpy(patterns[i], buffer);
    }
    Trie* trie = new_trie();
    for(int i = 0; i < n; i++) {
        add_string(trie, patterns[i]);
    } 
    print_trie(trie);
    delete_trie(&trie);
    for(int i = 0; i < n; i++) {
        free(patterns[i]);
    }
    free(buffer);
	return 0;
}

Trie* new_trie() {
    Trie* trie = malloc(sizeof(Trie));
    for(int i = 0; i < ALPHA_SIZE; i++) { 
        trie->next[i] = NULL;
    }
    return trie;
}

void add_string(Trie* trie, char* str) {
    int i = 0, size = strlen(str);
    while(i < size && trie->next[to_digit(str[i])]) {
        trie = trie->next[to_digit(str[i++])];
    }
    while(i < size) {
        trie->next[to_digit(str[i])] = new_trie();
        trie = trie->next[to_digit(str[i++])];
    }
}

void print_trie(Trie* trie) {
    int count = 0;
    print_trie_rec(trie, 0, &count);
}

void print_trie_rec(Trie* trie, int parent, int* count) {
    for(int i = 0; i < ALPHA_SIZE; i++) {
        if(trie->next[i]) {
            (*count)++;
            printf("%d->%d:%c\n", parent, *count, to_letter(i)); 
            print_trie_rec(trie->next[i], *count, count);
        }
    }
}

void delete_trie(Trie** trie) {
    if(*trie == NULL) {
        return;
    }
    for(int i = 0; i < ALPHA_SIZE; i++) {
        delete_trie(&(*trie)->next[i]);
    }
    free(*trie);
    *trie = NULL;
}

int to_digit(char c) {
    switch(c) {
        case 'A' : return 0; 
        case 'C' : return 1;
        case 'G' : return 2;
        case 'T' : return 3;
    }
}

char to_letter(int d) {
    switch(d) {
        case 0 : return 'A'; 
        case 1 : return 'C';
        case 2 : return 'G';
        case 3 : return 'T';
    }
}
