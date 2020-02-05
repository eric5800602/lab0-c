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
    /* Return NULL if malloc return NULL. */
    if (q == NULL) {
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
    if (q == NULL) {
        return;
    }
    /* Free all elements in queue. */
    while (q->head != NULL) {
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
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* Return NULL if malloc return NULL. */
    if (newh == NULL) {
        return false;
    }
    /* Allocate space for the string. */
    newh->value = malloc((strlen(s) + 1) * sizeof(char));
    /* Return NULL if malloc return NULL. */
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    /* Reset the space of string malloc just recently*/
    memset(newh->value, 0, sizeof(char) * (strlen(s) + 1));
    strncpy(newh->value, s, strlen(s));
    if (q->size == 0) {
        newh->next = NULL;
        q->head = newh;
        q->size++;
        return true;
    }
    newh->next = q->head;
    q->head = newh;
    /* If the tail in queue is NULL, assign newh to it. */
    if (q->tail == NULL) {
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
    if (q == NULL) {
        return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    /* Return NULL if malloc return NULL. */
    if (newt == NULL) {
        return false;
    }
    /* Allocate space for the string. */
    newt->value = malloc((strlen(s) + 1) * sizeof(char));
    /* Return NULL if malloc return NULL. */
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    /* Reset the space of string malloc just recently*/
    memset(newt->value, 0, strlen(s) + 1);
    strncpy(newt->value, s, strlen(s));
    newt->next = NULL;
    if (q->tail != NULL) {
        q->tail->next = newt;
    }
    q->tail = newt;
    /* If the head in queue is NULL, assign newt to it. */
    if (q->head == NULL) {
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
    if (q == NULL || q->size == 0) {
        return false;
    }
    /* If sp is non-NULL and an element is removed, copy the removed string to
     * *sp. */
    if (sp != NULL && q->head->value) {
        memset(sp, '\0', bufsize);
        strncpy(sp, q->head->value, bufsize - 1);
        printf("%s\n", sp);
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
    if (q != NULL && q->size) {
        return q->size;
    } else {
        return 0;
    }
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
}
