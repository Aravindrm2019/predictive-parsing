#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][20];
char leading[26][20], trailing[26][20];
int visitedLead[26], visitedTrail[26];
int n;

// Add symbol to set (avoid duplicates)
void add(char *set, char c) {
    for(int i = 0; set[i]; i++)
        if(set[i] == c) return;

    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
}

// LEADING function
void findLeading(char X) {

    if(visitedLead[X - 'A']) return;
    visitedLead[X - 'A'] = 1;

    for(int i = 0; i < n; i++) {

        if(prod[i][0] == X) {

            char c1 = prod[i][2]; // first symbol after =
            char c2 = (strlen(prod[i]) > 3) ? prod[i][3] : '\0';

            // Rule 1: A → a...
            if(!isupper(c1))
                add(leading[X - 'A'], c1);

            // Rule 2: A → B...
            if(isupper(c1))
                findLeading(c1);

            // Rule 3: A → Ba...
            if(isupper(c1) && !isupper(c2) && c2 != '\0')
                add(leading[X - 'A'], c2);
        }
    }
}

// TRAILING function
void findTrailing(char X) {

    if(visitedTrail[X - 'A']) return;
    visitedTrail[X - 'A'] = 1;

    for(int i = 0; i < n; i++) {

        if(prod[i][0] == X) {

            int len = strlen(prod[i]);
            char c1 = prod[i][len - 1]; // last symbol
            char c2 = (len > 3) ? prod[i][len - 2] : '\0';

            // Rule 1: A → ...a
            if(!isupper(c1))
                add(trailing[X - 'A'], c1);

            // Rule 2: A → ...B
            if(isupper(c1))
                findTrailing(c1);

            // Rule 3: A → ...aB
            if(isupper(c1) && !isupper(c2) && c2 != '\0')
                add(trailing[X - 'A'], c2);
        }
    }
}

int main() {

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (E=E+T format):\n");
    for(int i = 0; i < n; i++) {
        scanf("%s", prod[i]);
    }

    // Initialize
    for(int i = 0; i < 26; i++) {
        leading[i][0] = '\0';
        trailing[i][0] = '\0';
        visitedLead[i] = 0;
        visitedTrail[i] = 0;
    }

    // Compute
    for(int i = 0; i < n; i++) {
        findLeading(prod[i][0]);
        findTrailing(prod[i][0]);
    }

    // Print LEADING
    printf("\nLEADING Sets:\n");
    for(int i = 0; i < n; i++) {
        printf("LEADING(%c) = { %s }\n", prod[i][0], leading[prod[i][0]-'A']);
    }

    // Print TRAILING
    printf("\nTRAILING Sets:\n");
    for(int i = 0; i < n; i++) {
        printf("TRAILING(%c) = { %s }\n", prod[i][0], trailing[prod[i][0]-'A']);
    }

    return 0;
}