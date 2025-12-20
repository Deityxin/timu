#include <stdio.h>

int main(void) {
    int a;
    if (scanf("%d", &a) != 1) return 0;
    double sum = 0.0;
    int i = 0;
    while (sum <= a) {
        ++i;
        sum += 1.0 / i;
    }
    printf("%d\n", i);
    return 0;
}
