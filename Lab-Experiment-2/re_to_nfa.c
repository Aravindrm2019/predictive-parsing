#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// Structure for NFA state
typedef struct State {
    int id;
    struct State *out1, *out2;
    char symbol;
} State;

// Structure for NFA fragment
typedef struct Fragment {
    State *start;
    State *end;
} Fragment;

int state_id = 0;

// Create new state
State* newState(char symbol) {
    State *s = (State*)malloc(sizeof(State));
    s->id = state_id++;
    s->symbol = symbol;
    s->out1 = s->out2 = NULL;
    return s;
}

// Create fragment for symbol
Fragment createSymbol(char symbol) {
    State *s1 = newState(symbol);
    State *s2 = newState('\0');
    s1->out1 = s2;

    Fragment frag = {s1, s2};
    return frag;
}

// Concatenation
Fragment concat(Fragment f1, Fragment f2) {
    f1.end->out1 = f2.start;
    Fragment result = {f1.start, f2.end};
    return result;
}

// Union (|)
Fragment unionFrag(Fragment f1, Fragment f2) {
    State *start = newState('\0');
    State *end = newState('\0');

    start->out1 = f1.start;
    start->out2 = f2.start;

    f1.end->out1 = end;
    f2.end->out1 = end;

    Fragment result = {start, end};
    return result;
}

// Closure (*)
Fragment closure(Fragment f) {
    State *start = newState('\0');
    State *end = newState('\0');

    start->out1 = f.start;
    start->out2 = end;

    f.end->out1 = f.start;
    f.end->out2 = end;

    Fragment result = {start, end};
    return result;
}

// Stack for fragments
Fragment stack[MAX];
int top = -1;

void push(Fragment f) {
    stack[++top] = f;
}

Fragment pop() {
    return stack[top--];
}

// Main conversion
int main() {
    char regex[MAX];
    printf("Enter Regular Expression: ");
    scanf("%s", regex);

    for(int i = 0; i < strlen(regex); i++) {
        char c = regex[i];

        if(c == '*') {
            Fragment f = pop();
            push(closure(f));
        }
        else if(c == '.') {
            Fragment f2 = pop();
            Fragment f1 = pop();
            push(concat(f1, f2));
        }
        else if(c == '|') {
            Fragment f2 = pop();
            Fragment f1 = pop();
            push(unionFrag(f1, f2));
        }
        else {
            push(createSymbol(c));
        }
    }

    Fragment result = pop();

    printf("\nNFA constructed successfully!\n");
    printf("Start State: %d\n", result.start->id);
    printf("End State: %d\n", result.end->id);

    return 0;
}