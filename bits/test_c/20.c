#include <stdio.h>
#include <stdlib.h>
static long long *memo;
static long long legal(int n) {
    if (n == 1) return 1;
    if (memo[n] != 0) return memo[n];
    long long cnt = 1;
    for (int i = 1; i <= n / 2; ++i) cnt += legal(i);
    memo[n] = cnt;
    return cnt;
}
int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    memo = (long long *)calloc((size_t)n + 1, sizeof(long long));
    if (!memo) return 0;
    long long ans = legal(n);
    printf("%lld", ans);
    free(memo);
    return 0;
}