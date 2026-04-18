#include <stdio.h>
#include <string.h>

int main() {
    char exp[10];
    char op[10], arg1[10], arg2[10], result[10][10];
    int i = 0, j = 0, k = 0;
    char temp = '1';

    printf("Enter expression (e.g. a+b*c): ");
    scanf("%s", exp);

    printf("\nQuadruple Representation:\n");
    printf("Index\tOp\tArg1\tArg2\tResult\n");

    while(exp[i] != '\0') {

        if(exp[i] == '*' || exp[i] == '/' ||
           exp[i] == '+' || exp[i] == '-') {

            op[j] = exp[i];
            arg1[j] = exp[i-1];
            arg2[j] = exp[i+1];

            result[j][0] = 't';
            result[j][1] = temp++;
            result[j][2] = '\0';

            printf("%d\t%c\t%c\t%c\t%s\n",
                   j, op[j], arg1[j], arg2[j], result[j]);

            exp[i+1] = result[j][1]; // replace with temp
            j++;
        }
        i++;
    }

    // Triple
    printf("\nTriple Representation:\n");
    printf("Index\tOp\tArg1\tArg2\n");

    for(i = 0; i < j; i++) {
        printf("%d\t%c\t%c\t%c\n", i, op[i], arg1[i], arg2[i]);
    }

    // Indirect Triple
    printf("\nIndirect Triple:\n");
    printf("Pointer\tStatement\n");

    for(i = 0; i < j; i++) {
        printf("%d\t(%d)\n", i, i);
    }

    return 0;
}