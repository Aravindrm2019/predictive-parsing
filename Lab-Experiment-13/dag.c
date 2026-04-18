#include <stdio.h>
#include <string.h>

#define MAX 20

struct Node {
    char op;
    char left[10];
    char right[10];
    char result[10];
};

struct Node nodes[MAX];
int count = 0;

// Check if expression already exists
int findNode(char op, char *left, char *right) {
    for(int i = 0; i < count; i++) {
        if(nodes[i].op == op &&
           strcmp(nodes[i].left, left) == 0 &&
           strcmp(nodes[i].right, right) == 0) {
            return i;
        }
    }
    return -1;
}

int main() {

    char expr[20];
    char left[10], right[10], result[10], op;

    printf("Enter number of expressions: ");
    int n;
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {

        printf("Enter expression (a=b+c): ");
        scanf("%s", expr);

        // parse expression
        result[0] = expr[0]; result[1] = '\0';
        left[0] = expr[2]; left[1] = '\0';
        op = expr[3];
        right[0] = expr[4]; right[1] = '\0';

        int index = findNode(op, left, right);

        if(index != -1) {
            printf("Common subexpression found: %s reused\n", nodes[index].result);
            printf("%s = %s\n", result, nodes[index].result);
        } else {
            nodes[count].op = op;
            strcpy(nodes[count].left, left);
            strcpy(nodes[count].right, right);
            strcpy(nodes[count].result, result);

            count++;
        }
    }

    printf("\nOptimized DAG Nodes:\n");
    for(int i = 0; i < count; i++) {
        printf("%s = %s %c %s\n",
               nodes[i].result,
               nodes[i].left,
               nodes[i].op,
               nodes[i].right);
    }

    return 0;
}