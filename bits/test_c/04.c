#include <stdio.h>
#include <stdlib.h>

static int saved_money = 0;
static int have_money = 0;

static void handle_month(int spend, int idx) {
    have_money += 300;
    have_money -= spend;
    if (have_money < 0) {
        printf("-%d\n", idx + 1);
        exit(0);
    }
    int deposit = have_money / 100 * 100;
    saved_money += deposit;
    have_money -= deposit;
}

int main(void) {
    int expense[12];
    for (int i = 0; i < 12; ++i) {
        if (scanf("%d", &expense[i]) != 1) return 0;
    }
    for (int i = 0; i < 12; ++i) handle_month(expense[i], i);
    int total = (int)(saved_money * 1.2 + have_money + 1e-9);
    printf("%d\n", total);
    return 0;
}
