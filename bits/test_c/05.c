#include <stdio.h>

int main(void) {
    int work[7][2];
    for (int i = 0; i < 7; ++i) {
        if (scanf("%d%d", &work[i][0], &work[i][1]) != 2) return 0;
    }
    int best_day = 0;
    int best_sum = 0;
    for (int i = 0; i < 7; ++i) {
        int total = work[i][0] + work[i][1];
        if (total > 8 && total > best_sum) {
            best_sum = total;
            best_day = i + 1;
        }
    }
    printf("%d\n", best_day);
    return 0;
}
