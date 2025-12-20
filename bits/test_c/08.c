#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    long long c;
    if (scanf("%lld", &c) != 1) return 0;
    if (c == 0) {
        printf("0");
        return 0;
    }
    int negative = c < 0;
    if (negative) c = -c;
    char buf[32];
    sprintf(buf, "%lld", c);
    int len = (int)strlen(buf);
    int idx = len - 1;
    while (idx >= 0 && buf[idx] == '0') --idx;
    if (negative) putchar('-');
    for (; idx >= 0; --idx) putchar(buf[idx]);
    return 0;
}
