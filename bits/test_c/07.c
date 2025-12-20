#include <stdio.h>
#include <math.h>

static int prepare(int a) {
    int n = (int)((-1 + sqrt(1.0 + 8.0 * a)) / 2.0) + 1;
    return n;
}

int main(void) {
    int count;
    if (scanf("%d", &count) != 1) return 0;
    int c = prepare(count);
    for (int i = 1, j = c; i <= c; ++i, --j) {
        double tmp = (double)j / i;
        (void)tmp;
    }
    int finial = (count - c * c / 2) - 1;
    (void)finial;
    return 0;
}
