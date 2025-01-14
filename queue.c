#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (!new) {
        free(new);
        new = NULL;
        return NULL;
    }

    INIT_LIST_HEAD(new);
    return new;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    struct list_head *temp;
    temp = l->next;
    while (temp != l) {
        element_t *node = container_of(temp, element_t, list);
        temp = temp->next;
        free(node->value);
        free(node);
    }
    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *node = (element_t *) malloc(sizeof(element_t));
    if (!node)
        return false;
    if (!node->value) {
        free(node);
        node = NULL;
        return false;
    }
    node->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    memcpy(node->value, s, strlen(s));
    node->value[strlen(s)] = '\0';
    list_add(&node->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *node = (element_t *) malloc(sizeof(element_t));
    if (!node)
        return false;
    if (!node->value) {
        free(node);
        node = NULL;
        return false;
    }
    node->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    memcpy(node->value, s, strlen(s));
    node->value[strlen(s)] = '\0';
    list_add(&node->list, head->prev);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head)
        return NULL;

    if (head->next == head)
        return NULL;

    element_t *data = list_entry(head->next, element_t, list);
    memcpy(sp, data->value, strlen(data->value));
    sp[strlen(data->value)] = '\0';

    list_del(head->next);

    return data;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head)
        return NULL;

    if (head->prev == head)
        return NULL;

    element_t *data = list_entry(head->prev, element_t, list);
    memcpy(sp, data->value, strlen(data->value));
    sp[strlen(data->value)] = '\0';

    list_del(head->prev);

    return data;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *li;

    /*
     *for (node = (head)->next; node != (head); node = node->next)
     *  len++;
     */
    list_for_each (li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head)
        return false;

    if (head->next == head) {
        return false;
    }

    if (head->next->next == head) {
        return false;
    }

    int mid = q_size(head) / 2;
    struct list_head *node = head->next;
    for (int i = 0; i < mid; i++)
        node = node->next;

    list_del(node);

    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head) {}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
int q_merge(struct list_head *head)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
