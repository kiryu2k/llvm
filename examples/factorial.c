#include <stdio.h>

int factorial(int n) { return n == 0 ? 1 : n * factorial(n - 1); }

int main() {
    int n;
    int f;
    printf("Enter an integer to find its factorial\n");
    scanf("%d", &n);
    if (n < 0) {
        printf("Factorial of negative integers isn't defined.\n");
        return 1;
    }
    f = factorial(n);
    printf("%d! = %d\n", n, f);
    return 0;
}