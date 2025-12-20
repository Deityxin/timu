#include <stdio.h>

int main(void) {
    int a, b;
    if (scanf("%d%d", &a, &b) != 2) return 0;
    int total_money = a * 10 + b;
    int price = 19;
    printf("%d\n", total_money / price);
    return 0;
}
