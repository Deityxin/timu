#include <stdio.h>
long long add(long long x, long long y) {
    return x + y;
}
int main(void) {
    long long a, b;
    if (scanf("%lld%lld", &a, &b) != 2) return 0;
    printf("%lld\n", add(a, b));
    return 0;
}
