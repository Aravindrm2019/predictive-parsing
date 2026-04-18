#include <stdio.h>
#include <ctype.h>

#define MAX 20

char stack[MAX][10];
int top = -1;

void push(char *str) {
    strcpy(stack[++top], str);
}

char* pop() {
    return stack[top--];
}

int main() {

    char postfix[20];
    int i = 0;
    char temp[5] = "t0";
    int tempCount = 1;

    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    printf("\nTarget Code:\n");

    while(postfix[i] != '\0') {

        // Operand
        if(isalnum(postfix[i])) {
            char op[2] = {postfix[i], '\0'};
            push(op);
        }

        // Operator
        else {
            char *op2 = pop();
            char *op1 = pop();

            printf("MOV R0, %s\n", op1);

            switch(postfix[i]) {
                case '+': printf("ADD R0, %s\n", op2); break;
                case '-': printf("SUB R0, %s\n", op2); break;
                case '*': printf("MUL R0, %s\n", op2); break;
                case '/': printf("DIV R0, %s\n", op2); break;
            }

            // store result in temp
            char res[5];
            sprintf(res, "t%d", tempCount++);
            printf("MOV %s, R0\n", res);

            push(res);
        }
        i++;
    }

    printf("\nFinal Result in %s\n", stack[top]);

    return 0;
}