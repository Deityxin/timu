#include <stdio.h>
#include <stdlib.h>

static int is_leap(int y) {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

static int days_in_month(int y, int m) {
    static const int md[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2) return is_leap(y) ? 29 : 28;
    return md[m - 1];
}

int main(void) {
    char s1[16], s2[16];
    if (scanf("%15s%15s", s1, s2) != 2) return 0;
    int l = atoi(s1);
    int r = atoi(s2);
    int ans = 0;
    for (int y = 1000; y <= 9999; ++y) {
        int m = (y % 10) * 10 + (y / 10) % 10;
        int d = (y / 100) % 10 * 10 + (y / 1000);
        if (m < 1 || m > 12) continue;
        if (d < 1 || d > days_in_month(y, m)) continue;
        int date = y * 10000 + m * 100 + d;
        if (date >= l && date <= r) ++ans;
    }
    printf("%d", ans);
    return 0;
}