#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

char productions[MAX][10];
char first[26][10], follow[26][10];
int n;

void add(char *set, char c) {
    for(int i = 0; set[i]; i++)
        if(set[i] == c) return;
    int len = strlen(set);
    set[len] = c;
    set[len+1] = '\0';
}

void findFirst(char X) {
    for(int i = 0; i < n; i++) {
        if(productions[i][0] == X) {
            char c = productions[i][2];

            if(c == '#') {
                add(first[X-'A'], '#');
            }
            else if(!isupper(c)) {
                add(first[X-'A'], c);
            }
            else {
                findFirst(c);
                for(int j = 0; first[c-'A'][j]; j++)
                    add(first[X-'A'], first[c-'A'][j]);
            }
        }
    }
}

void findFollow(char X) {
    if(X == productions[0][0])
        add(follow[X-'A'], '$');

    for(int i = 0; i < n; i++) {
        for(int j = 2; productions[i][j]; j++) {
            if(productions[i][j] == X) {
                char next = productions[i][j+1];

                if(next) {
                    if(!isupper(next)) {
                        add(follow[X-'A'], next);
                    } else {
                        for(int k = 0; first[next-'A'][k]; k++) {
                            if(first[next-'A'][k] != '#')
                                add(follow[X-'A'], first[next-'A'][k]);
                        }
                    }
                } else {
                    if(productions[i][0] != X)
                        findFollow(productions[i][0]);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (E=TR format, # for epsilon):\n");
    for(int i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    // Initialize
    for(int i = 0; i < 26; i++) {
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    // FIRST
    for(int i = 0; i < n; i++) {
        findFirst(productions[i][0]);
    }

    // FOLLOW
    for(int i = 0; i < n; i++) {
        findFollow(productions[i][0]);
    }

    // Print FIRST
    printf("\nFIRST Sets:\n");
    for(int i = 0; i < n; i++) {
        printf("FIRST(%c) = { %s }\n", productions[i][0], first[productions[i][0]-'A']);
    }

    // Print FOLLOW
    printf("\nFOLLOW Sets:\n");
    for(int i = 0; i < n; i++) {
        printf("FOLLOW(%c) = { %s }\n", productions[i][0], follow[productions[i][0]-'A']);
    }

    return 0;
}