#ifndef H_LINKED_LISTS_H
#define H_LINKED_LISTS_H
typedef struct node {
    int data;
    struct node * next;
} node;
typedef void (*callback)(node* data);
node* create(int data,node* next);
node* append(node* head, int data);
node* remove_front(node* head);
 #endif /∗ H_LINKED_LISTS_H */
