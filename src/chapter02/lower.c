/*
 * lower()
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * lower(): Converts a character to lower space
 */

static char lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}


int main(void) {

    (void)putchar(lower('T'));
    (void)putchar(lower('t'));
    (void)putchar('\n');

    exit(EXIT_SUCCESS);
}
