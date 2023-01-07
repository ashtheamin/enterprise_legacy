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

Facility list metadata:
facility_list->id_last_assigned: This is incremented by 1 every time a new
facility is added in order to ensure no two facilities ever have the same ID.

facility_list->id_currently_selected: This is the ID that is selected in the
facility editor dialogue.
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

    return facility;
}

// Facility list metadata structure.
struct facility_list {
    struct facility_node* head;
    char id_last_assigned[ENTERPRISE_STRING_LENGTH];
    char id_currently_selected[ENTERPRISE_STRING_LENGTH];
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
    {facility_node_linked_list_free(facility_list->head);}

    free(facility_list);
    return;
}

// Append a new facility to a facility list.
void facility_list_append(struct facility_list* facility_list) {
    if (facility_list == NULL) return;

    // Increment unique ID by 1.
    char buffer[ENTERPRISE_STRING_LENGTH];
    sprintf(buffer, "%lld", atoll(facility_list->id_last_assigned)+1);
    strcpy(facility_list->id_last_assigned, buffer);

    // Add new node to start of facility list if facility linked list does
    // not exist.
    if (facility_list->head == NULL) {
        facility_list->head = facility_node_new();
        strcpy(facility_list->head->id, facility_list->id_last_assigned);
        strcpy(facility_list->id_currently_selected,\
        facility_list->id_last_assigned);
        return;
    }

    // Else add the new node to the end of the list.
    struct facility_node* facility = facility_list->head;
    while (facility->next != NULL) {
        facility = facility->next;
    }
    facility->next = facility_node_new();
    facility->next->prev = facility;

    strcpy(facility->next->id, facility_list->id_last_assigned);
    strcpy(facility_list->id_currently_selected,\
    facility_list->id_last_assigned);
    
    return;
}

// Get the number of facility nodes in the facility list
int facility_list_get_num_facility_nodes(struct facility_list* facility_list) {
    if (facility_list == NULL) return 0;
    if (facility_list->head == NULL) return 0;

    struct facility_node* facility = facility_list->head;
    int facility_count = 0;
    while (facility != NULL) {
        facility_count++;
        facility = facility->next;
    }
    return facility_count;
}

// Return a pointer to a facility node according to ID. 
// Returns NULL on failure.
struct facility_node* facility_list_get_node\
(struct facility_list* facility_list, char* id) {
    if (facility_list == NULL || id == NULL) return NULL;
    if (facility_list->head == NULL) return NULL;

    struct facility_node* facility = facility_list->head;
    while (facility != NULL) {
        if (strcmp(facility->id, id) == 0) return facility;
        facility = facility->next;
    }
    return NULL;
}

// Searches for a facility by ID and deletes it
void facility_list_delete_node(struct facility_list* facility_list, char* id) {

}