#include <stdint.h>
#include <math.h>
#include <stdio.h>

uint64_t s(int n) {
    return 0;
}

long double f(int n) {
    return pow(log(n*sqrt(30)), 3)/(6*log(2)*log(3)*log(5));
}

uint64_t hamber(int n)
{
    return f(n) + log(log(n));
}

int main() {
    for (int i = 1; i < 120; i++) {
        printf("%li\n", hamber(i));
    }
    return 0;
}