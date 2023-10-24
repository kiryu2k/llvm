#include <stdio.h>

int fib(int n) {
    if (n < 3) {
        return 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main() {
    const int n = 9;
    printf("%d\n", fib(n));
    return 0;
}