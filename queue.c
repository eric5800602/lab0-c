#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "natsort/strnatcmp.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* Return NULL if malloc return NULL. */
    if (!q) {
        return NULL;
    }
    memset(q, 0, sizeof(queue_t));
    q->head = NULL;
    q->tail = NULL;
    /* Initial the size of queue to zero. */
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Free queue structure */
    /* Check whether q is NULL. */
    if (!q) {
        return;
    }
    /* Free all elements in queue. */
    while (q->head) {
        list_ele_t *tmp = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = tmp;
    }
    free(q);
    return;
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
    /* Check whether q is NULL. */
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* Return NULL if malloc return NULL. */
    if (!newh) {
        return false;
    }
    /* Allocate space for the string. */
    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    /* Return NULL if malloc return NULL. */
    if (!newh->value) {
        free(newh);
        return false;
    }
    /* Reset the space of string malloc just recently*/
    memset(newh->value, 0, sizeof(char) * (strlen(s) + 1));
    strncpy(newh->value, s, strlen(s));
    newh->next = q->head;
    q->head = newh;
    /* If the tail in queue is NULL, assign newh to it. */
    if (!q->tail) {
        q->tail = newh;
    }
    /* The size of queue plus one. */
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
    /* Check whether q is NULL. */
    if (!q) {
        return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    /* Return NULL if malloc return NULL. */
    if (!newt) {
        return false;
    }
    /* Allocate space for the string. */
    newt->value = malloc(sizeof(char) * (strlen(s) + 1));
    /* Return NULL if malloc return NULL. */
    if (!newt->value) {
        free(newt);
        return false;
    }
    /* Reset the space of string malloc just recently*/
    memset(newt->value, 0, sizeof(char) * (strlen(s) + 1));
    strncpy(newt->value, s, strlen(s));
    newt->next = NULL;
    if (q->tail) {
        q->tail->next = newt;
    }
    q->tail = newt;
    /* If the head in queue is NULL, assign newt to it. */
    if (!q->head) {
        q->head = newt;
    }
    /* The size of queue plus one. */
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
    /* Return false if queue is NULL or empty. */
    if (!q || !q->size) {
        return false;
    }
    /* If sp is non-NULL and an element is removed, copy the removed string to
     * *sp. */
    /* If sp is non-NULL and an element is removed,
       copy the removed string to *sp. */
    if (sp != NULL && q->head->value) {
        memset(sp, '\0', bufsize);
        strncpy(sp, q->head->value, bufsize - 1);
    }
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    /* Free the spaces used by the list element and the string. */
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q && q->size) {
        return q->size;
    }
    return 0;
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
    /* Return if queue is NULL or empty. */
    if (!q || q->size == 0 || q->size == 1) {
        return;
    }
    /* Declare back & front pointer for reversing. */
    list_ele_t *back, *front;
    /* Reverse elements in queue. */
    /* Change the tail of queue and record previous pointer in back. */
    q->tail = q->head;
    back = q->head;
    /* Move the head pointer to the next and record next pointer in fornt. */
    q->head = q->head->next;
    front = q->head->next;
    /* Clear the next of tail to NULL*/
    q->tail->next = NULL;
    while (front) {
        /* Change the next pointer of current head to previous. */
        q->head->next = back;
        /* Repeat recording back & front pointer and move the head of q to the
         * next. */
        back = q->head;
        /* Wrong writage: q->head = q->head->next. Because q->head->next had
         * been changed before. */
        q->head = front;
        front = q->head->next;
    }
    q->head->next = back;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */

void q_sort(queue_t *q)
{
    // merge sort
    if (!q || q->size == 1 || q->size == 0) {
        return;
    }
    q->head = mergeSortList(q->head);
    /* Check the tail of queue. */
    list_ele_t *tail = q->head;
    while (tail->next) {
        tail = tail->next;
    }
    q->tail = tail;
}
list_ele_t *mergeSortList(list_ele_t *head)
{
    // merge sort
    if (!head || !head->next)
        return head;

    list_ele_t *fast = head->next;
    list_ele_t *slow = head;

    // split list
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    fast = slow->next;
    slow->next = NULL;

    // sort each list
    list_ele_t *l1 = mergeSortList(head);
    list_ele_t *l2 = mergeSortList(fast);

    // merge sorted l1 and sorted l2
    return merge(l1, l2);
}

list_ele_t *merge(list_ele_t *l1, list_ele_t *l2)
{
    /* Using merge with pseudo node will cause following error
     * FATAL ERROR: Calls to malloc disallowed
     * FATAL Error.  Exiting
     */
    /* Declare pointer q as result for returning. */
    list_ele_t *temp = NULL, *q = NULL;
    /* Initial temp and q pointers for merge starting. */
    if (strnatcmp(l1->value, l2->value) < 0) {
        q = l1;
        temp = q;
        l1 = l1->next;
    } else {
        q = l2;
        temp = q;
        l2 = l2->next;
    }
    /* Merge two list(l1 & l2) until the end of one. */
    while (l1 && l2) {
        if (strnatcmp(l1->value, l2->value) < 0) {
            temp->next = l1;
            temp = temp->next;
            l1 = l1->next;
        } else {
            temp->next = l2;
            temp = temp->next;
            l2 = l2->next;
        }
    }
    /* Another list may not be over yet. */
    if (l1)
        temp->next = l1;
    if (l2)
        temp->next = l2;

    return q;
}