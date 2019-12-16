#include <stdlib.h>
#include "h/xmalloc.h"
#include "h/linked-list.h"

conscell *ll_push(conscell *list, void *data)
{
    conscell *new = xmalloc(sizeof *new);
    new->data = data;
    new->next = list;
    return new;
}
conscell *ll_pop(conscell *list)
{
    if(list == NULL) {
        return NULL;
    }
    conscell *front = list;
    list = list->next;
    front->next = NULL;
    /* is this the last node in the list */
    if(front == list)
        list = NULL;
    free(front);
    return list;
}
void ll_free(conscell *list) // version1: iterative
{
    while (list != NULL) {
        conscell *p = list->next; // rememberthenextnode
        free(list); // freetheheadnode
        list = p; // produceashorterlist
    }
}
conscell *ll_reverse(conscell *list){
    conscell* prev = NULL;
    conscell* current = list;
    conscell* next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list = prev;
    return list;
}

conscell *ll_filter(conscell *list,
                    int (*filter)(const void *a),
                    conscell **removed) {
    if (list == NULL) {
        return list;
    } else if (filter(list->data)) {
        conscell *p =list->next;
        list->next = *removed;
        *removed = list;
    } else {
        list->next = ll_filter(list->next, filter, removed);
        return list;
    }
}
