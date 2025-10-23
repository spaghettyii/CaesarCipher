#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTRINGLEN 10000

typedef struct dict_node node_t;
struct dict_node {
    char val;
    struct dict_node *next[26];
};

typedef node_t *dict_header_t;

void error(int type)
{
    if (type == 1) {
        printf("malloc error\n");
        exit(-1);
    }
    if (type == 2) {
        printf("NULL passed to function error\n");
        exit(-2);
    }
    printf("default error");
    exit(-3);
}

dict_header_t *initialize()
{
    dict_header_t *new_dict = malloc(sizeof(dict_header_t));
    if (new_dict == NULL) error(1);
    for (int i = 0; i < 26; i++)
        new_dict[i] = NULL;
    return new_dict;
}

void free_dict(dict_header_t *dict)
{
    for (int i = 0; i < 26; i++)
        free(dict[i]);
    return;
}

int charidx(char c) 
//@requires c to be part of english alphabet in ASCII
{
    return (65 <= c && c <= 90) ? (int)c - 65 : (int)c - 97;
}

void insert_word(dict_header_t *dict, char *word)
//@requires word != NULL;
{
    if (word == NULL) error(2);
    int idx = charidx(first_char);
    while (word[0] != '\0')
    {
        if (dict[idx] == NULL) {
            dict[idx] = malloc(sizeof(node_t));
        }
        dict[idx]->val = word[0];
        dict = dict[idx]->next;
    }
}

void insert_word(dict_header_t *dict, char *word)
//@requires word != NULL;
{
    if (word == NULL || dict == NULL) error(2);
    char first_char = word[0];
    if (first_char == '\0') return;
    
    int idx = charidx(first_char);
    if (dict[idx] == NULL) dict[idx] = malloc(sizeof(node_t));
    dict[idx]->val = first_char;
    dict = dict[idx]->next;
    word = word + 1; 
    insert_word(dict, word);
    return;
}

int main (int argc, char *argv[])
{
    // By most frequent
    char freq[26] = "etaoinshrdlcumwfgypbvkjxqz";
    short counts[26] = {0};

    char s[MAXSTRINGLEN] = "";
    printf("what is the cipher text you want decrypted?\n");
    fgets(s, MAXSTRINGLEN, stdin);
    printf("your deciphered text is:\n");

    long length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        char c = s[i];
        if (65 <= c && c <= 90)
           counts[c-65]++; 
        else if (97 <= c && c <= 122) 
            counts[c-97]++;
    }
    

    return 0;
}
