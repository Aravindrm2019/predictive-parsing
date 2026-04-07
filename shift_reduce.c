#include <stdio.h>
#include <string.h>

char stack[50];
int top = -1;
char input[50];

void push(char c) {
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void pop(int n) {
    top -= n;
    stack[top + 1] = '\0';
}

int main() {
    int i = 0;
    char action[10];

    printf("Enter the input string: ");
    scanf("%s", input);

    printf("\nStack\t\tInput\t\tAction\n");
    printf("--------------------------------------------------\n");

    while (1) {
        // Shift operation
        push(input[i]);
        printf("%s\t\t%s\t\tShift\n", stack, input + i + 1);
        i++;

        // Reduce: E → id
        if (stack[top] == 'd' && stack[top - 1] == 'i') {
            pop(2);
            push('E');
            printf("%s\t\t%s\t\tReduce: E->id\n", stack, input + i);
        }

        // Reduce: E → E+E
        if (stack[top] == 'E' && stack[top - 1] == '+' && stack[top - 2] == 'E') {
            pop(3);
            push('E');
            printf("%s\t\t%s\t\tReduce: E->E+E\n", stack, input + i);
        }

        // Accept condition
        if (stack[0] == 'E' && stack[1] == '\0' && input[i] == '\0') {
            printf("%s\t\t%s\t\tAccept\n", stack, input + i);
            break;
        }

        // Error condition
        if (input[i] == '\0' && !(stack[0] == 'E' && stack[1] == '\0')) {
            printf("%s\t\t%s\t\tReject\n", stack, input + i);
            break;
        }
    }

    return 0;
}