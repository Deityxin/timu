#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char s[64];
    if (!fgets(s, sizeof(s), stdin)) return 0;
    size_t len = strlen(s);
    if (len && s[len - 1] == '\n') s[--len] = '\0';
    int digits[9];
    int idx = 0;
    for (size_t i = 0; s[i] && idx < 9; ++i) {
        if (isdigit((unsigned char)s[i])) digits[idx++] = s[i] - '0';
    }
    int sum = 0;
    for (int i = 0; i < 9; ++i) sum += digits[i] * (i + 1);
    int d = sum % 11;
    char e = (d == 10) ? 'X' : (char)('0' + d);
    if (e == s[len - 1]) {
        printf("Right");
    } else {
        s[len - 1] = e;
        printf("%s", s);
    }
    return 0;
}
