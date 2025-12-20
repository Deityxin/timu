#include <stdio.h>
#include <string.h>

int main(void) {
    char s[10005];
    if (!fgets(s, sizeof(s), stdin)) return 0;
    size_t cnt = 0;
    for (size_t i = 0; i < strlen(s); ++i) {
        if (s[i] != ' ' && s[i] != '\n') ++cnt;
    }
    printf("%zu", cnt);
    return 0;
}
