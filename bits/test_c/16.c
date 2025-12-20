#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void to_lower_str(char *s) {
    for (; *s; ++s) *s = (char)tolower((unsigned char)*s);
}

int main(void) {
    char pat[205];
    char text[10005];
    if (!fgets(pat, sizeof(pat), stdin)) return 0;
    if (!fgets(text, sizeof(text), stdin)) return 0;

    size_t pat_len = strlen(pat);
    if (pat_len && pat[pat_len - 1] == '\n') pat[--pat_len] = '\0';
    size_t text_len = strlen(text);
    if (text_len && text[text_len - 1] == '\n') text[--text_len] = '\0';

    to_lower_str(pat);
    to_lower_str(text);

    int cnt = 0;
    int first = -1;
    size_t i = 0;
    while (i < text_len) {
        while (i < text_len && text[i] == ' ') ++i;
        if (i >= text_len) break;
        size_t start = i;
        while (i < text_len && text[i] != ' ') ++i;
        size_t len = i - start;
        if (len == pat_len && strncmp(text + start, pat, pat_len) == 0) {
            if (cnt == 0) first = (int)start;
            ++cnt;
        }
    }

    if (cnt == 0) {
        printf("-1");
    } else {
        printf("%d %d", cnt, first);
    }
    return 0;
}