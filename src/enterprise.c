
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include "constants.c"
#include "facilities.c"

// The enterprise struct.
// This holds all relevant database information about the enterprise.
struct enterprise {
    char name[ENTERPRISE_STRING_LENGTH];
    char balance[ENTERPRISE_STRING_LENGTH];
};

// Enterprise instance constructor.
// Returns pointer to enterprise on success, else returns NULL.
struct enterprise* enterprise_new() {
    struct enterprise* enterprise = malloc(sizeof(struct enterprise));
    if (enterprise == NULL) return NULL;

    strcpy(enterprise->name, "");
    strcpy(enterprise->balance, "");
    return enterprise;
}

// Frees memory associated with enterprise.
void enterprise_quit(struct enterprise* enterprise) {
    if (enterprise == NULL) return;
    free(enterprise);
    return;
}