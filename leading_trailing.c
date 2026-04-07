#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][MAX];
char leading[MAX][MAX], trailing[MAX][MAX];
int n;

// Function to add symbol to set (avoid duplicates)
void addToSet(char *set, char symbol) {
    for (int i = 0; set[i] != '\0'; i++) {
        if (set[i] == symbol)
            return;
    }
    int len = strlen(set);
    set[len] = symbol;
    set[len + 1] = '\0';
}

// Find LEADING
void findLeading(char nt, int index) {
    for (int i = 0; i < n; i++) {
        if (productions[i][0] == nt) {
            // A → a...
            if (!isupper(productions[i][2])) {
                addToSet(leading[index], productions[i][2]);
            }
            else {
                // A → B...
                findLeading(productions[i][2], productions[i][2] - 'A');
                
                // Add LEADING(B)
                for (int k = 0; leading[productions[i][2] - 'A'][k] != '\0'; k++) {
                    addToSet(leading[index], leading[productions[i][2] - 'A'][k]);
                }

                // A → Ba...
                if (productions[i][3] != '\0' && !isupper(productions[i][3])) {
                    addToSet(leading[index], productions[i][3]);
                }
            }
        }
    }
}

// Find TRAILING
void findTrailing(char nt, int index) {
    for (int i = 0; i < n; i++) {
        int len = strlen(productions[i]);
        if (productions[i][0] == nt) {
            // A → ...a
            if (!isupper(productions[i][len - 1])) {
                addToSet(trailing[index], productions[i][len - 1]);
            }
            else {
                // A → ...B
                findTrailing(productions[i][len - 1], productions[i][len - 1] - 'A');

                // Add TRAILING(B)
                for (int k = 0; trailing[productions[i][len - 1] - 'A'][k] != '\0'; k++) {
                    addToSet(trailing[index], trailing[productions[i][len - 1] - 'A'][k]);
                }

                // A → ...aB
                if (len > 3 && !isupper(productions[i][len - 2])) {
                    addToSet(trailing[index], productions[i][len - 2]);
                }
            }
        }
    }
}

int main() {
    int i;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (E=E+T format):\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    // Initialize sets
    for (i = 0; i < MAX; i++) {
        leading[i][0] = '\0';
        trailing[i][0] = '\0';
    }

    // Compute LEADING & TRAILING
    for (i = 0; i < n; i++) {
        findLeading(productions[i][0], productions[i][0] - 'A');
        findTrailing(productions[i][0], productions[i][0] - 'A');
    }

    // Display LEADING
    printf("\nLEADING:\n");
    for (i = 0; i < 26; i++) {
        if (leading[i][0] != '\0') {
            printf("%c : { ", i + 'A');
            for (int j = 0; leading[i][j] != '\0'; j++) {
                printf("%c ", leading[i][j]);
            }
            printf("}\n");
        }
    }

    // Display TRAILING
    printf("\nTRAILING:\n");
    for (i = 0; i < 26; i++) {
        if (trailing[i][0] != '\0') {
            printf("%c : { ", i + 'A');
            for (int j = 0; trailing[i][j] != '\0'; j++) {
                printf("%c ", trailing[i][j]);
            }
            printf("}\n");
        }
    }

    return 0;
}