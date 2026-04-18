#include <stdio.h>

#define MAX 10

int n;
int gen[MAX], kill[MAX], in[MAX], out[MAX];

// Print set
void printSet(int set[]) {
    printf("{ ");
    for(int i = 0; i < n; i++) {
        if(set[i])
            printf("d%d ", i);
    }
    printf("}");
}

int main() {

    printf("Enter number of blocks: ");
    scanf("%d", &n);

    // Input GEN and KILL
    for(int i = 0; i < n; i++) {
        printf("\nBlock %d:\n", i);

        printf("GEN: ");
        scanf("%d", &gen[i]);

        printf("KILL: ");
        scanf("%d", &kill[i]);

        in[i] = 0;
        out[i] = gen[i]; // initial
    }

    // Iterative computation
    int changed;
    do {
        changed = 0;

        for(int i = 0; i < n; i++) {

            int old_out = out[i];

            // IN[B] = OUT[B-1] (simple linear CFG)
            if(i == 0)
                in[i] = 0;
            else
                in[i] = out[i-1];

            // OUT[B] = GEN ∪ (IN - KILL)
            out[i] = gen[i] | (in[i] & !kill[i]);

            if(old_out != out[i])
                changed = 1;
        }

    } while(changed);

    // Output
    printf("\nFinal Data Flow Sets:\n");

    for(int i = 0; i < n; i++) {
        printf("Block %d:\n", i);
        printf("IN  = %d\n", in[i]);
        printf("OUT = %d\n", out[i]);
    }

    return 0;
}