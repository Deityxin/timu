#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int l, m;
    if (scanf("%d%d", &l, &m) != 2) return 0;
    int *keep = (int *)malloc((l + 1) * sizeof(int));
    if (!keep) return 0;
    for (int i = 0; i <= l; ++i) keep[i] = 1;
    for (int i = 0; i < m; ++i) {
        int a, b;
        if (scanf("%d%d", &a, &b) != 2) break;
        if (a < 0) a = 0;
        if (b > l) b = l;
        for (int x = a; x <= b; ++x) keep[x] = 0;
    }
    int count = 0;
    for (int i = 0; i <= l; ++i) if (keep[i]) ++count;
    printf("%d", count);
    free(keep);
    return 0;
}
