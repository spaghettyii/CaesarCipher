#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXSTRINGLEN 10000
#define MAXWORDLEN 100

typedef struct dict_node node_t;
struct dict_node {
    struct dict_node *next_list[26];
    char val;
    bool valid_word;
};

void error(int type)
{
    switch (type) {
        case 1:
            printf("malloc error\n");
            break;
        case 2:
            printf("NULL passed to function error\n");
            break;
        case 3:
            printf("file open error\n");
            break;
        default:
            printf("default error");
    }
    exit(-type);
    return;
}

node_t *initialize()
{
    node_t *new_dict = malloc(sizeof(node_t));
    if (new_dict == NULL) error(1);
    new_dict->val = '\0';
    new_dict->valid_word = false;
    for (int i = 0; i < 26; i++)
        new_dict->next_list[i] = NULL;
    return new_dict;
}

void free_dict(node_t *dict)
{
    for (int i = 0; i < 26; i++)
        free(dict->next_list[i]);
    free(dict);
    return;
}

int charidx(char c) 
//@requires c to be part of english alphabet in ASCII
{
    return (65 <= c && c <= 90) ? (int)c - 65 : (int)c - 97;
}

void insert_word(node_t *wordp, char *word)
//@requires word != NULL;
{
    if (word == NULL) error(2);
    char next_char = word[0];
    int iter = 0;
    int idx = charidx(next_char);
    while (next_char != '\0' && next_char != '\n')
    {
        if (wordp->next_list[idx] == NULL) {
            wordp->next_list[idx] = malloc(sizeof(node_t));
            wordp->next_list[idx]->val = next_char;
            wordp->next_list[idx]->valid_word = false;
        }
        wordp = wordp->next_list[idx];
        next_char = word[++iter];
        idx = charidx(next_char);
    }
    wordp->valid_word = true;
    return;
}

void print_dict(node_t *root, char *accword, int len)
//@requires accword to be the start of a buffer in which
// the traversal will collect the words.
// prints the current dictionary in inorder traversal order
{
    if (root == NULL) {
        return;
    }

    accword[len] = root->val;
    if (root->valid_word) {
        for (int i = 1; i <= len; i++)
            printf("%c", accword[i]);
        printf("\n");
    }
    len++;
    for (int i = 0; i < 26; i++)
        print_dict(root->next_list[i], accword, len);
    return;
}

bool find_word(node_t *root, char *word)
//@requires root != NULL
//@requires word != NULL
//@ensures true if word is found from the root of the tree
{
    if (word == NULL || root == NULL) return false;
    char next_char = word[0];
    int iter = 0;
    node_t *wordp = root;
    while (next_char != '\0' && next_char != '\n')
    {
        int idx = charidx(next_char);
        if (wordp->next_list[idx] == NULL) return false;
        wordp = wordp->next_list[idx];
        next_char = word[++iter];
    }
    return wordp->valid_word;
}

node_t *get_eng_dict()
{
    node_t *english_dict = initialize();
    FILE *fptr = fopen("/usr/share/dict/words", "r");
    if (fptr == NULL) error(3);

    char temp[MAXWORDLEN];
    while (fgets(temp, MAXWORDLEN, fptr))
        insert_word(english_dict, temp);

    return english_dict;
}

char rotate(char c, int k)
{
    return ('a' <= c && c <= 'z') ? ((c - 'a' + k) % 26) + 'a' : ((c - 'A' + k) % 26) + 'a'; 
}

void decrypt(node_t *english, char *cyphertext)
{
    int len = strlen(cyphertext) - 1;
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < len; j++) {
            char c = cyphertext[j];
            if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
                cyphertext[j] = rotate(c, 1);
        }
        char temp[len+1];
        strncpy(temp, cyphertext, len + 1);
        if (find_word(english, strtok(temp, " \n\0")))
            printf("%s", cyphertext);
    }
    return;
}

void encrypt(char *message, int shift)
{
    int len = strlen(message) - 1;
    for (int i = 0; i < len; i++) {
        char c = message[i];
        if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))
            message[i] = rotate(message[i], shift);
    }
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

    node_t *english = get_eng_dict();
    // char tempbuffer[100];
    // print_dict(english, &tempbuffer, 0);

    printf("possible decryptions:\n");
    decrypt(english, s);

    return 0;
}
