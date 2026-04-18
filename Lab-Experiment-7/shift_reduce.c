#include <stdio.h>
#include <string.h>

char stack[20], input[20];
int top = -1;

void shift(char symbol) {
    stack[++top] = symbol;
    stack[top + 1] = '\0';
}

void reduce() {
    // E → id
    if(top >= 1 && stack[top] == 'd' && stack[top-1] == 'i') {
        stack[top-1] = 'E';
        top--;
        printf("Reduce: E->id\n");
    }

    // E → E+E
    else if(top >= 2 && stack[top] == 'E' && stack[top-1] == '+' && stack[top-2] == 'E') {
        stack[top-2] = 'E';
        top -= 2;
        printf("Reduce: E->E+E\n");
    }

    // E → E*E
    else if(top >= 2 && stack[top] == 'E' && stack[top-1] == '*' && stack[top-2] == 'E') {
        stack[top-2] = 'E';
        top -= 2;
        printf("Reduce: E->E*E\n");
    }

    // E → (E)
    else if(top >= 2 && stack[top] == ')' && stack[top-1] == 'E' && stack[top-2] == '(') {
        stack[top-2] = 'E';
        top -= 2;
        printf("Reduce: E->(E)\n");
    }
}

int main() {
    int i = 0;
    stack[0] = '\0';

    printf("Enter input string (use i for id): ");
    scanf("%s", input);

    printf("\nStack\tInput\tAction\n");

    while(1) {
        reduce();

        if(input[i] != '\0') {
            printf("%s\t%s\tShift\n", stack, input + i);
            shift(input[i]);
            i++;
        } else {
            reduce();
            if(strcmp(stack, "E") == 0) {
                printf("%s\t\tAccept\n", stack);
            } else {
                printf("%s\t\tReject\n", stack);
            }
            break;
        }
    }

    return 0;
}