#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int priority(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

void reverse(char exp[]) {
    int i, j;
    char temp;
    for (i = 0, j = strlen(exp) - 1; i < j; i++, j--) {
        temp = exp[i];
        exp[i] = exp[j];
        exp[j] = temp;
    }
}

int main() {
    char infix[50], postfix[50];
    int i, j = 0;

    printf("Enter infix expression: ");
    scanf("%s", infix);

    reverse(infix);

    for (i = 0; infix[i]; i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }

    for (i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(') {
            push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (stack[top] != '(')
                postfix[j++] = pop();
            pop();
        }
        else {
            while (top != -1 && priority(stack[top]) > priority(infix[i]))
                postfix[j++] = pop();
            push(infix[i]);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';

    reverse(postfix);

    printf("Prefix: %s\n", postfix);
    return 0;
}