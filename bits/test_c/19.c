#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Str {
    char *data;
    size_t len;
    size_t cap;
};

static void str_init(struct Str *s) {
    s->data = NULL;
    s->len = s->cap = 0;
}

static void str_pushc(struct Str *s, char c) {
    if (s->len + 1 >= s->cap) {
        size_t nc = s->cap ? s->cap * 2 : 64;
        char *tmp = (char *)realloc(s->data, nc);
        if (!tmp) return;
        s->data = tmp;
        s->cap = nc;
    }
    s->data[s->len++] = c;
    s->data[s->len] = '\0';
}

static void read_block(struct Str *s) {
    char buf[2048];
    while (fgets(buf, sizeof(buf), stdin)) {
        size_t len = strlen(buf);
        while (len && (buf[len - 1] == '\n' || buf[len - 1] == '\r')) buf[--len] = '\0';
        if (strcmp(buf, "EOF") == 0) break;
        if (s->len) str_pushc(s, '\n');
        for (size_t i = 0; i < len; ++i) str_pushc(s, buf[i]);
    }
}

static void apply_backspace(struct Str *s) {
    size_t w = 0;
    for (size_t i = 0; i < s->len; ++i) {
        char c = s->data[i];
        if (c == '<') {
            if (w && s->data[w - 1] != '\n') --w;
        } else {
            s->data[w++] = c;
        }
    }
    s->len = w;
    if (s->cap) s->data[w] = '\0';
}

static int match_count(const char *s, const char *a) {
    int count = 0;
    const char *p = s;
    const char *q = a;
    while (*p || *q) {
        const char *np = strchr(p, '\n');
        const char *nq = strchr(q, '\n');
        size_t len_p = np ? (size_t)(np - p) : strlen(p);
        size_t len_q = nq ? (size_t)(nq - q) : strlen(q);
        size_t limit = len_p < len_q ? len_p : len_q;
        for (size_t i = 0; i < limit; ++i) {
            if (p[i] == q[i]) ++count;
        }
        p += len_p + (np ? 1 : 0);
        q += len_q + (nq ? 1 : 0);
        if (!np && !nq) break;
    }
    return count;
}

int main(void) {
    struct Str s, a;
    str_init(&s);
    str_init(&a);
    read_block(&s);
    read_block(&a);
    apply_backspace(&s);
    apply_backspace(&a);
    int n = 0;
    if (scanf("%d", &n) != 1) n = 0;
    int fin = match_count(s.data ? s.data : "", a.data ? a.data : "");
    int finial = (n > 0) ? (int)(fin * 60.0 / n + 0.5) : 0;
    printf("%d", finial);
    free(s.data);
    free(a.data);
    return 0;
}