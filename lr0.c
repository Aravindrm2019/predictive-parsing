#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20
#define MAX_PROD 20

char productions[MAX_PROD][20];
char items[MAX][MAX][20];   // States → items
int state_count = 0, prod_count;

// Add dot at beginning
void addDot(char *prod, char *result) {
    result[0] = prod[0];
    result[1] = '-';
    result[2] = '>';
    result[3] = '.';
    strcpy(result + 4, prod + 3);
}

// Check if item already exists in state
int exists(char state[MAX][20], int count, char *item) {
    for (int i = 0; i < count; i++) {
        if (strcmp(state[i], item) == 0)
            return 1;
    }
    return 0;
}

// Closure function
void closure(char state[MAX][20], int *count) {
    int i, j;
    for (i = 0; i < *count; i++) {
        char *dot = strchr(state[i], '.');
        if (dot && isupper(*(dot + 1))) {
            char B = *(dot + 1);

            for (j = 0; j < prod_count; j++) {
                if (productions[j][0] == B) {
                    char newItem[20];
                    addDot(productions[j], newItem);

                    if (!exists(state, *count, newItem)) {
                        strcpy(state[*count], newItem);
                        (*count)++;
                    }
                }
            }
        }
    }
}

// Move dot over symbol
void gotoState(char state[MAX][20], int count, char symbol, char newState[MAX][20], int *newCount) {
    *newCount = 0;

    for (int i = 0; i < count; i++) {
        char temp[20];
        strcpy(temp, state[i]);

        char *dot = strchr(temp, '.');
        if (dot && *(dot + 1) == symbol) {
            // Swap dot and symbol
            char t = *(dot);
            *(dot) = *(dot + 1);
            *(dot + 1) = t;

            strcpy(newState[*newCount], temp);
            (*newCount)++;
        }
    }

    closure(newState, newCount);
}

// Compare states
int sameState(char a[MAX][20], int countA, char b[MAX][20], int countB) {
    if (countA != countB) return 0;

    for (int i = 0; i < countA; i++) {
        int found = 0;
        for (int j = 0; j < countB; j++) {
            if (strcmp(a[i], b[j]) == 0)
                found = 1;
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    int i, j;

    printf("Enter number of productions: ");
    scanf("%d", &prod_count);

    printf("Enter productions (E->E+T format):\n");
    for (i = 0; i < prod_count; i++) {
        scanf("%s", productions[i]);
    }

    // Initial state I0
    int count = 0;
    addDot(productions[0], items[0][count++]);
    closure(items[0], &count);

    int state_size[MAX];
    state_size[0] = count;
    state_count = 1;

    // Generate states
    for (i = 0; i < state_count; i++) {
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            char newState[MAX][20];
            int newCount;

            gotoState(items[i], state_size[i], ch, newState, &newCount);

            if (newCount == 0) continue;

            int found = -1;
            for (j = 0; j < state_count; j++) {
                if (sameState(items[j], state_size[j], newState, newCount)) {
                    found = j;
                    break;
                }
            }

            if (found == -1) {
                for (j = 0; j < newCount; j++)
                    strcpy(items[state_count][j], newState[j]);

                state_size[state_count] = newCount;
                state_count++;
            }
        }
    }

    // Display states
    printf("\nLR(0) Item Sets:\n");
    for (i = 0; i < state_count; i++) {
        printf("\nI%d:\n", i);
        for (j = 0; j < state_size[i]; j++) {
            printf("%s\n", items[i][j]);
        }
    }

    return 0;
}
