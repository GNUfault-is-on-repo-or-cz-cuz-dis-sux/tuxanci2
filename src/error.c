#include <stdio.h>

void error(const char *error) {
    fprintf(stderr, "Error: %s\n", error);
}