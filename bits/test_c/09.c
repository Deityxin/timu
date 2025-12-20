#include <stdio.h>

int main(void) {
    const int bench = 30;
    int apple[10];
    for (int i = 0; i < 10; ++i) {
        if (scanf("%d", &apple[i]) != 1) return 0;
    }
    int max, count = 0;
    if (scanf("%d", &max) != 1) return 0;
    for (int j = 0; j < 10; ++j) {
        if (apple[j] <= max + bench) ++count;
    }
    printf("%d", count);
    return 0;
}
