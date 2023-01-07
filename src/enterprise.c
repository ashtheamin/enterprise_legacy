
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

/* What does this file do?
It provides the enterprise data structure, which holds all the data related to
the enterprise. It stores lists of everything needed in an enterprise.
*/

// The enterprise struct.
// This holds all relevant database information about the enterprise.
struct enterprise {
    char name[ENTERPRISE_STRING_LENGTH];
    char balance[ENTERPRISE_STRING_LENGTH];
    struct facility_list* facility_list;
};

// Enterprise instance constructor.
// Returns pointer to enterprise on success, else returns NULL.
struct enterprise* enterprise_new() {
    struct enterprise* enterprise = malloc(sizeof(struct enterprise));
    if (enterprise == NULL) return NULL;

    strcpy(enterprise->name, "");
    strcpy(enterprise->balance, "");
    enterprise->facility_list = facility_list_new();
    return enterprise;
}

// Frees memory associated with enterprise.
void enterprise_quit(struct enterprise* enterprise) {
    if (enterprise == NULL) return;
    if (enterprise->facility_list != NULL) 
        {facility_list_free(enterprise->facility_list);}
    free(enterprise);
    return;
}