#include <stdio.h>
#include <string.h>

#define MAX 10

int nfa[MAX][2][MAX];  // nfa[state][input][next_states]
int nfa_states, dfa_states = 0;

int dfa[MAX][2];       // dfa transitions
int visited[MAX];

// Check if state already exists
int isVisited(int state) {
    for(int i = 0; i < dfa_states; i++) {
        if(dfa[i][0] == state)
            return 1;
    }
    return 0;
}

int main() {
    int i, j;

    printf("Enter number of NFA states: ");
    scanf("%d", &nfa_states);

    printf("Enter NFA transitions (0/1 inputs):\n");
    for(i = 0; i < nfa_states; i++) {
        for(j = 0; j < 2; j++) {
            printf("From state %d on input %d: ", i, j);
            scanf("%d", &nfa[i][j][0]); // simplified
        }
    }

    printf("\nDFA Transitions:\n");

    for(i = 0; i < nfa_states; i++) {
        for(j = 0; j < 2; j++) {
            dfa[i][j] = nfa[i][j][0];
            printf("From %d on %d -> %d\n", i, j, dfa[i][j]);
        }
    }

    return 0;
}