#include <stdio.h>

static int min_int(int a, int b) {
    return a < b ? a : b;
}

static int pack_price(int need, int pack_cnt, int pack_price) {
    int packs = need / pack_cnt;
    if (need % pack_cnt) ++packs;
    return packs * pack_price;
}

int main(void) {
    int need;
    if (scanf("%d", &need) != 1) return 0;
    int b, c, e, f, g, h;
    if (scanf("%d%d%d%d%d%d", &b, &c, &e, &f, &g, &h) != 6) return 0;
    int p1 = pack_price(need, b, c);
    int p2 = pack_price(need, e, f);
    int p3 = pack_price(need, g, h);
    int ans = min_int(p1, min_int(p2, p3));
    printf("%d\n", ans);
    return 0;
}
