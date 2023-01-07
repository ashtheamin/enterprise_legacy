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

/* How facilities work.
Facilities are stored in a struct that contains a pointer to the head of a
linked list containing all the facilities. The struct that stores the linked 
list is directly added to the enterprise struct and stores metadata about the
list. All facilities are assigned a unique ID, no two facilities can have the
same ID, the facility_list structure keeps track of that.

Data structures:
Facility_node: An individual facility.
Facility_list: A structure holding important metadata about the facility 
linked list.
*/

// Facility node.
struct facility_node {
    char id[ENTERPRISE_STRING_LENGTH];
    char name[ENTERPRISE_STRING_LENGTH];
    char email[ENTERPRISE_STRING_LENGTH];
    char phone[ENTERPRISE_STRING_LENGTH];
    char address[ENTERPRISE_STRING_LENGTH];

    struct facility_node* prev;
    struct facility_node* next;
};

// Facility node constructor and initialiser.
// Returns facility node on success, or NULL on failure.
struct facility_node* facility_node_new() {
    struct facility_node* facility = malloc(sizeof(struct facility_node));
    if (facility == NULL) return NULL;
    strcpy(facility->id, "");
    strcpy(facility->name, "");
    strcpy(facility->email ,"");
    strcpy(facility->phone, "");
    strcpy(facility->address, "");
    
    facility->prev = NULL;
    facility->next = NULL;
}

// Facility list metadata structure.
struct facility_list {
    struct facility_node* head;
};

// Facility list constructor.
// Returns facility list on success, or NULL on failure.
struct facility_list* facility_list_new() {
    struct facility_list* facility_list = malloc(sizeof(struct facility_list));
    if (facility_list == NULL) return NULL;
    facility_list->head = NULL;
    return facility_list;
}

// Free an entire facility linked list
void facility_node_linked_list_free(struct facility_node* facility) {
    if (facility == NULL) return;
    struct facility_node* next = NULL;
    while (facility != NULL) {
        next = facility->next;
        free(facility);
        facility = next;
    }
}

// Free all memory associated with a facility list.
void facility_list_free(struct facility_list* facility_list) {
    if (facility_list == NULL) return;

    if (facility_list->head != NULL) 
    {facility_node_linked_list_free(facility_list->head);

    free(facility_list);
    return;
}