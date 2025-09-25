#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *link;
} node_t;

node_t *iterate(node_t *head, int index) {
    node_t *current = head;

    int current_index = 0;

    while (current->link != NULL && (current_index < index || index == -1)) {
        current = current->link;
        current_index++;
    }

    return current;
}

int find(node_t *head, int value) {
    node_t *current = head;

    int current_index = 0;

    while (current->link != NULL) {
        if (current->data == value) return current_index;
        current = current->link;
        current_index++;
    }

    return -1;
}

void add_node(node_t **head, int index, int data) {
    node_t *current = iterate(*head, index);

    if (index == 0) {
        node_t *new = (node_t*)malloc(sizeof(node_t));

        new->data = data;
        new->link = *head;
        *head = new;
    }
    else {
        node_t *previous = iterate(*head, index-1);
        node_t *new = (node_t*)malloc(sizeof(node_t));

        new->data = data;
        
        if (previous->link == NULL) {
            new->link = NULL;
        }
        else {
            new->link = current;
        }

        previous->link = new;
    }
}

void pop_node(node_t **head, int index) {
    node_t *current = iterate(*head, index);

    if (index == 0) {
        *head = current->link;
    }
    else {
        node_t *previous = iterate(*head, index-1);
        previous->link = current->link;
    }
    free(current);
}

node_t *convert(node_t *head, int arr[], int len) {
    head->data = arr[0];
    head->link = NULL;

    for (int i = 1; i < len; i++) {
        add_node(&head, i, arr[i]);
    }

    return head;
}

void print(node_t *head) {
    node_t *current = head;

    while (current != NULL) {
        printf("%d->", current->data);
        current = current->link;
    }
    printf("NULL\n");
}

void free_list(node_t *head) {
    node_t *current = head;
    
    while (current != NULL) {
        node_t *next = current->link;
        free(current);
        current = next;
    }
}

node_t *partition(node_t *head) {
    if (head->link == NULL) return head;

    node_t *current = head->link;
    node_t *l_head = (node_t*)malloc(sizeof(node_t));
    l_head->data = -1;
    node_t *r_head = (node_t*)malloc(sizeof(node_t));
    r_head->data = -1;

    while (current != NULL) {
        if (current->data <= head->data) {
            if (l_head->data == -1) l_head->data = current->data;
            else {
                node_t *last = iterate(l_head, -1);
                node_t *new = (node_t*)malloc(sizeof(node_t));

                new->data = current->data;

                last->link = new;
            }
        }
        else {
            if (r_head->data == -1) r_head->data = current->data;
            else {
                node_t *last = iterate(r_head, -1);
                node_t *new = (node_t*)malloc(sizeof(node_t));

                new->data = current->data;

                last->link = new;
            }
        }

        current = current->link;
    }

    node_t *l_sorted = partition(l_head);
    node_t *r_sorted = partition(r_head);

    iterate(l_sorted, -1)->link = head;
    head->link = r_sorted;

    return l_sorted;
}

node_t *quicksort(node_t *head) {
    head = partition(head);

    while (find(head, -1) != -1) {
        pop_node(&head, find(head, -1));
    }

    return head;
}

int main() {
    int arr[] = {4,7,3,2,9};
    int length = sizeof(arr)/sizeof(arr[0]);

    node_t *head = (node_t*)malloc(sizeof(node_t));

    convert(head, arr, length);

    head = quicksort(head);
    print(head);

    free_list(head);
    return 0;
}
