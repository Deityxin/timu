#include <stdio.h>
#include <stdlib.h>

struct Vec {
    int *data;
    int size;
    int cap;
};

static void vec_init(struct Vec *v) {
    v->data = NULL;
    v->size = v->cap = 0;
}

static void vec_push(struct Vec *v, int val) {
    if (v->size == v->cap) {
        int nc = v->cap ? v->cap * 2 : 4;
        int *tmp = (int *)realloc(v->data, nc * sizeof(int));
        if (!tmp) return;
        v->data = tmp;
        v->cap = nc;
    }
    v->data[v->size++] = val;
}

int main(void) {
    int n, m, k;
    if (scanf("%d%d%d", &n, &m, &k) != 3) return 0;
    struct Vec *day = (struct Vec *)malloc((k + 1) * sizeof(struct Vec));
    if (!day) return 0;
    for (int i = 0; i <= k; ++i) vec_init(&day[i]);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int val;
            if (scanf("%d", &val) != 1) val = 0;
            if (val >= 1 && val <= k) vec_push(&day[val], j + 1);
        }
    }

    for (int d = 1; d <= k; ++d) {
        int seen_size = m + 1;
        char *seen = (char *)calloc(seen_size, sizeof(char));
        int unique = 0;
        for (int i = 0; i < day[d].size; ++i) {
            int paper = day[d].data[i];
            if (paper >= 1 && paper <= m && !seen[paper]) {
                seen[paper] = 1;
                ++unique;
            }
        }
        free(seen);
        if (d > 1) putchar(' ');
        printf("%d", unique);
    }
    for (int i = 0; i <= k; ++i) free(day[i].data);
    free(day);
    return 0;
}
