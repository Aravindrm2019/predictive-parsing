#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

// Stack functions
void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

char peek() {
    return stack[top];
}

// Precedence
int precedence(char c) {
    if(c == '+' || c == '-') return 1;
    if(c == '*' || c == '/') return 2;
    if(c == '^') return 3;
    return 0;
}

// Infix to Postfix
void infixToPostfix(char infix[], char postfix[]) {
    int i, j = 0;

    for(i = 0; infix[i]; i++) {

        if(isalnum(infix[i])) {
            postfix[j++] = infix[i];
        }

        else if(infix[i] == '(') {
            push(infix[i]);
        }

        else if(infix[i] == ')') {
            while(peek() != '(')
                postfix[j++] = pop();
            pop(); // remove '('
        }

        else {
            while(top != -1 && precedence(peek()) >= precedence(infix[i]))
                postfix[j++] = pop();
            push(infix[i]);
        }
    }

    while(top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

// Reverse string
void reverse(char str[]) {
    int i, j;
    char temp;
    int len = strlen(str);

    for(i = 0, j = len - 1; i < j; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

// Infix to Prefix
void infixToPrefix(char infix[], char prefix[]) {
    char temp[MAX];

    strcpy(temp, infix);

    reverse(temp);

    // swap brackets
    for(int i = 0; temp[i]; i++) {
        if(temp[i] == '(') temp[i] = ')';
        else if(temp[i] == ')') temp[i] = '(';
    }

    infixToPostfix(temp, prefix);
    reverse(prefix);
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    // reset stack
    top = -1;

    infixToPrefix(infix, prefix);

    printf("\nPostfix: %s", postfix);
    printf("\nPrefix: %s\n", prefix);

    return 0;
}
