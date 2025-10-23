#include <stdio.h>
#include <string.h>

#define MAXSTRINGLEN 10000

int main(int argc, char *argv[])
{
    char s[MAXSTRINGLEN] = "";
    int shift = 0;
    printf("what is the cipher text you want decrypted?\n");
    fgets(s, MAXSTRINGLEN, stdin);
    printf("and by how much shift?\n");
    scanf("%d", &shift);
    printf("your deciphered text is:\n");

    long length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        char c = s[i];
        // Character is upper case
        if (65 <= c && c <= 90) {
            char m = ((c - 65 - shift) % 26) + 65;
            printf("%c", m);
        } else if (97 <= c && c <= 122) {
            char m = ((c - 97 - shift) % 26) + 97;
            printf("%c", m);
        } else { printf("%c", c); }
    }
    printf("\n");

    return 0;
}
