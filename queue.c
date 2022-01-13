#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q) {
        return NULL;
    }
    /* TODO: What if malloc returned NULL? */
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */

    if (!q)
        return;
    while (q_remove_head(q, NULL, 0))
        ;

    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->value = malloc(sizeof(char) * strlen(s) + 1);
    if (!newh->value) {
        free(newh);
        return false;
    }
    /* initial newh->value*/
    memset(newh->value, '\0', strlen(s) + 1);
    strncpy(newh->value, s, strlen(s) + 1);

    /* check queue empty*/
    if (!q->head) {
        q->head = newh;
        q->tail = newh;
        newh->next = NULL;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    newt->value = malloc(sizeof(char) * strlen(s) + 1);
    if (!newt->value) {
        free(newt);
        return false;
    }
    /*initial value*/
    memset(newt->value, '\0', strlen(s) + 1);
    strncpy(newt->value, s, strlen(s) + 1);
    /*check queue empty*/
    if (!q->tail) {
        q->head = newt;
        q->tail = newt;
        newt->next = NULL;
    } else {
        list_ele_t *node = q->tail;
        node->next = newt;
        newt->next = NULL;
        q->tail = newt;
    }
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    /*check queue empty*/
    if (!q || !q->head)
        return false;
    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, q->head->value, bufsize - 1);
    }
    list_ele_t *temp = q->head;
    q->head = q->head->next;
    free(temp->value);
    free(temp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return;
    list_ele_t *m = NULL;     // head
    list_ele_t *n = q->head;  // head next
    list_ele_t *o = n->next;  // head next next
    while (o) {
        n->next = m;

        // m n o node forward a next
        m = n;
        n = o;
        o = o->next;
    }
    n->next = m;
    q->tail = q->head;
    q->head = n;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !q->head)
        return;

    mergeSort(&q->head);  // many sort function


    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}

void mergeSort(list_ele_t **head)
{
    if (!(*head) || !((*head)->next))
        return;

    list_ele_t *slow = *head;
    list_ele_t *fast = (*head)->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;
    slow = *head;  // let me think

    mergeSort(&slow);
    mergeSort(&fast);

    *head = merge(slow, fast);
}

list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    list_ele_t *newt = NULL;
    list_ele_t **cursor = &newt;

    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) < 0) {
            *cursor = l1;
            l1 = l1->next;
        } else {
            *cursor = l2;
            l2 = l2->next;
        }
        //*cursor = (*cursor)->next;
        cursor = &(*cursor)->next;
    }

    if (!l1)
        *cursor = l2;
    else
        *cursor = l1;

    return newt;
}
