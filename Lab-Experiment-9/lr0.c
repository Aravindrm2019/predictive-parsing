#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char prod[MAX][20];
int n;

// Function to print item with dot at position
void printItem(char *production, int dot) {
    printf("%c->", production[0]);
    for(int i = 2; i < strlen(production); i++) {
        if(i == dot) printf(".");
        printf("%c", production[i]);
    }
    if(dot == strlen(production))
        printf(".");
    printf("\n");
}

// Closure function
void closure() {
    printf("\nLR(0) Items (Closure):\n");

    for(int i = 0; i < n; i++) {
        int len = strlen(prod[i]);

        // Generate all dot positions
        for(int j = 2; j <= len; j++) {
            printItem(prod[i], j);
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

    closure();

    return 0;
}