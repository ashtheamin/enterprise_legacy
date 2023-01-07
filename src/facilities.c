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

struct facility_node {
    char id[ENTERPRISE_STRING_LENGTH];
    char name[ENTERPRISE_STRING_LENGTH];
    char email[ENTERPRISE_STRING_LENGTH];
    char address[ENTERPRISE_STRING_LENGTH];

    struct facility_node* prev;
    struct facility_node* next;
};

struct facility_list {
    struct facility_node* head;
};