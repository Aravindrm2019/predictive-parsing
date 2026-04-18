#include <stdio.h>
#include <string.h>

int main() {
    char nonTerminal, alpha[10], beta[10];

    printf("Enter Non-Terminal (E): ");
    scanf("%c", &nonTerminal);

    printf("Enter alpha (recursive part): ");
    scanf("%s", alpha);

    printf("Enter beta (non-recursive part): ");
    scanf("%s", beta);

    printf("\nAfter Removing Left Recursion:\n");

    printf("%c -> %s%c'\n", nonTerminal, beta, nonTerminal);
    printf("%c' -> %s%c' | ε\n", nonTerminal, alpha, nonTerminal);

    return 0;
}