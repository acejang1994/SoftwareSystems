/* Example code for Software Systems at Olin College.

Based on an example from http://www.learn-c.org/en/Linked_lists

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int val;
    struct node *next;
} Node;

Node *make_node(int val, Node *next) {
    Node *node = malloc(sizeof(Node));
    node->val = val;
    node->next = next;
    return node;
}

void print_list(Node *head) {
    Node *current = head;

    while (current != NULL) {
        printf("%d\n", current->val);
        current = current->next;
    }
    printf("%s\n", "-------");
}

int pop(Node **head) {
    int retval;
    Node *next_node;
    Node *local;

    if (*head == NULL) {
        return -1;
    }
    local = *head;
    next_node = (local)->next;
    retval = (local)->val;
    free(local);
    *head = next_node;

    return retval;
}

// Add a new element to the beginning of the list.
void push(Node **head, int val) {
    // FILL THIS IN!
    Node *push_node = make_node(val, *head);
    *head = push_node;

}

// Remove the first element with the given value; return the number
// of nodes removed.
int remove_by_value(Node **head, int val) {
    // FILL THIS IN!
    Node *current = *head;
    Node *previous;

    // if (head->val == val){
    if (current->val == val){
        pop(head);
        return 1;

    }
    while (current != NULL) {
        if (current->val == val){
            *previous->next = *(current->next);
            return 1; 
        }
        previous = current;
        current = current->next;
    }
    
    return 0;
}

// Reverse the elements of the list without allocating new nodes.
void reverse(Node **head) {
    // FILL THIS IN!
    Node *next;
    Node *current = *head;
    Node *previous = NULL;

    while(current != NULL){
        next = current->next;
        current->next = previous;
        
        previous = current;
        current = next;

    }
    *head = previous;
}


int main() {
    Node *test_list = make_node(1, NULL);
    test_list->next = make_node(2, NULL);
    test_list->next->next = make_node(3, NULL);
    test_list->next->next->next = make_node(4, NULL);

    print_list(test_list);

    int retval = pop(&test_list);
    push(&test_list, retval+10);
    print_list(test_list);

    remove_by_value(&test_list, 11);
    
    // remove_by_value(&test_list, 3);
    remove_by_value(&test_list, 7);

    print_list(test_list);

    reverse(&test_list);

    print_list(test_list);
}
