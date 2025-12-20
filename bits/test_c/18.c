#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int cmp(const void *a, const void *b) {
    const char *x = *(const char **)a;
    const char *y = *(const char **)b;
    size_t lx = strlen(x), ly = strlen(y);
    char xy[128], yx[128];
    snprintf(xy, sizeof(xy), "%s%s", x, y);
    snprintf(yx, sizeof(yx), "%s%s", y, x);
    int r = strcmp(yx, xy);
    return r;
}

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    char **arr = (char **)malloc(n * sizeof(char *));
    if (!arr) return 0;
    for (int i = 0; i < n; ++i) {
        char buf[64];
        if (scanf("%63s", buf) != 1) buf[0] = '\0';
        arr[i] = (char *)malloc(strlen(buf) + 1);
        if (!arr[i]) return 0;
        strcpy(arr[i], buf);
    }

    qsort(arr, n, sizeof(char *), cmp);

    int all_zero = 1;
    for (int i = 0; i < n; ++i) {
        if (strcmp(arr[i], "0") != 0) { all_zero = 0; break; }
    }
    if (all_zero) {
        printf("0");
    } else {
        for (int i = 0; i < n; ++i) printf("%s", arr[i]);
    }

    for (int i = 0; i < n; ++i) free(arr[i]);
    free(arr);
    return 0;
}