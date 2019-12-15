#include <stdio.h>
#include "linked-list.h"
#include "xmalloc.h"
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
int main() {
    conscell *list = NULL; // an empty list
    int a = 101, b = -45, c = 1000, d = 12;
    list = ll_push(list, &a);
    list = ll_push(list, &b);
    list = ll_push(list, &c);
    list = ll_push(list, &d);
    printf("the original linked list:\n");
    for (conscell *p = list; p != NULL; p = p->next) {
        printf("%d ", *(int *) p->data);
    }
    //putchar(’\n’);
    return 0;
}