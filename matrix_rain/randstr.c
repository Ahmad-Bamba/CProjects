#include "randstr.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>

char const* const randstr_sparkle = "/?.*&%+#-^`";

char const* randstr_generate(size_t n)
{
    char* buf = malloc(n + 1);

    if (buf == NULL) {
        return NULL;
    }

    if (n == 0) {
        buf[0] = '\0';
        return buf;
    }

    srand(time(NULL));

    int i;
    for (i = 0; i < n; i++) {
        buf[i] = rand() % 93 + 33;
    }

    buf[n] = '\0';
    return buf;
}

char const* randstr_spacer(size_t n)
{
    char* buf = malloc(n + 1);

    if (buf == NULL) {
        return NULL;
    }

    memset(buf, ' ', n);
    buf[n] = '\0';

    return buf;
}
