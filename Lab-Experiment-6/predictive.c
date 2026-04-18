#include <stdio.h>
#include <string.h>

int main() {

    printf("Predictive Parsing Table:\n\n");

    printf("      id     +      *      (      )      $\n");
    printf("------------------------------------------------\n");

    printf("E   | E->TE' |      |      | E->TE' |      |      |\n");
    printf("E'  |        | E'->+TE' |      |      | E'->e | E'->e |\n");
    printf("T   | T->FT' |      |      | T->FT' |      |      |\n");
    printf("T'  |        | T'->e | T'->*FT' |      | T'->e | T'->e |\n");
    printf("F   | F->id  |      |      | F->(E) |      |      |\n");

    return 0;
}