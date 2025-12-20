#include <stdio.h>

int main(void) {
    long long num[100000];
    int sz = 0;
    long long v;
    do {
        if (scanf("%lld", &v) != 1) return 0;
        num[sz++] = v;
    } while (v != 0 && sz < 100000);
    if (sz == 1) return 0;
    for (int i = sz - 2; i >= 0; --i) {
        if (i != sz - 2) putchar(' ');
        printf("%lld", num[i]);
    }
    return 0;
}
