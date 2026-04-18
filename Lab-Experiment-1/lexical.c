#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Function to check keyword
int isKeyword(char word[]) {
    char *keywords[] = {
        "int", "float", "char", "if", "else",
        "while", "for", "return", "void"
    };
    
    int n = 9;
    for(int i = 0; i < n; i++) {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int main() {
    char input[200], word[50];
    int i = 0, j;

    printf("Enter source code:\n");
    fgets(input, sizeof(input), stdin);

    while(input[i] != '\0') {

        // Identifier / Keyword
        if(isalpha(input[i]) || input[i] == '_') {
            j = 0;
            while(isalnum(input[i]) || input[i] == '_') {
                word[j++] = input[i++];
            }
            word[j] = '\0';

            if(isKeyword(word))
                printf("%s : Keyword\n", word);
            else
                printf("%s : Identifier\n", word);
        }

        // Numbers
        else if(isdigit(input[i])) {
            j = 0;
            while(isdigit(input[i])) {
                word[j++] = input[i++];
            }
            word[j] = '\0';
            printf("%s : Number\n", word);
        }

        // Operators
        else if(strchr("+-*/=%<>!", input[i])) {
            printf("%c : Operator\n", input[i]);
            i++;
        }

        // Special Symbols
        else if(strchr("(){}[],;", input[i])) {
            printf("%c : Special Symbol\n", input[i]);
            i++;
        }

        // Skip spaces
        else if(isspace(input[i])) {
            i++;
        }

        else {
            printf("%c : Unknown\n", input[i]);
            i++;
        }
    }

    return 0;
}