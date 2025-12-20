#include <stdio.h>

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    int a[200];
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    int count = 0;
    for (int j = 0; j < n; ++j) {
        int found = 0;
        for (int k = 0; k < n && !found; ++k) {
            for (int l = k + 1; l < n; ++l) {
                if (a[j] == a[k] + a[l]) {
                    ++count;
                    found = 1;
                    break;
                }
            }
        }
    }
    printf("%d", count);
    return 0;
}
