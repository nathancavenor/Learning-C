#include <stdio.h>

int main(void) {
    double a, b, sum;
    char op;

    printf("Enter an expression: ");
    scanf("%lf %c %lf", &a, &op, &b);

    if (op == '+')
        sum = a + b;
    else if (op == '*')
        sum = a * b;
    else if (op == '/')
        sum = b != 0 ? a/b : 0;
    else if (op == '-')
        sum = a - b;
    else {
        printf("What operator is that??\n");
        return 1;
    }

    printf("Result: %.2f\n", sum);
    return 0;
}