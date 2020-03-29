/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));

	/* allocation falis */
	if (!q) return NULL;

	q->tail = NULL;
    q->head = NULL;
	q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
	// if q is NULL, do nothing
	if (!q) return;
    /* Free queue structure */
	list_ele_t *cur = q->head, *nex = NULL;

	while (cur) {
		nex = cur->next;
		free(cur->value);
		free(cur);
		cur = nex;
	}

	free(q);
}

static int stringLength(char *s) {
	// return the length of the C-string 
	int num = 0;
	while (s[num] != '\0') num++;

	return num + 1;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
	if (!q) return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

	if (!newh) {
		return false;
	}
    /* Don't forget to allocate space for the string and copy it */
	char* t = malloc(sizeof(char) * (stringLength(s)));
	if (!t) {
		free(newh);
		return false;
	}

	// copy the string
	strcpy(t, s);
	newh->value = t;
	
	newh->next = q->head;
	q->head = newh;

	// update the tail
	if (!q->tail) q->tail = newh;

	++q->size;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

	// if q is NULL
	if (!q) return false;

	list_ele_t *newtail = malloc(sizeof(list_ele_t));
	if (!newtail) {
		return false;
	}

	newtail->value = malloc(sizeof(char) * stringLength(s));
	if (!newtail->value) {
		free(newtail);
		return false;
	}

	strcpy(newtail->value, s);
	newtail->next = NULL;

	if (!q->tail) {
		q->head = newtail;
		q->tail = newtail;
	} else {
		q->tail->next = newtail;
		q->tail = newtail;
	}
	
	// update the size of the queue, no matter the queue is empty or not
	q->size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
	// if q is null or empty
	if (!q || !q->head) {
		return false;
	}

	list_ele_t *newhead = q->head->next, *oldhead = q->head;

	// if sp is not null, copy the removed string to it
	if (sp) {
		int i;
		for (i = 0; i < bufsize - 1 && *(q->head->value + i) != '\0'; ++i) {
			*(sp + i) = *(q->head->value + i);
		}
		*(sp + i) = '\0';
	}

	free(oldhead->value);
	free(oldhead);

	// update head of queue
	q->head = newhead;

	// update size of queue
	q->size -= 1;

	return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
	if (!q || !q->head) {
		return 0;
	}

	return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
	if (!q || !q->head) {
		return ;
	}

	// record the tail
	list_ele_t *oldhead = q->head, *oldtail = q->tail;

	// reverse
	list_ele_t *cur = q->head, *nex = NULL, *prev = NULL;

	while (cur) {
		nex = cur->next;
		cur->next = prev;
		prev = cur;
		cur = nex;
	}

	q->head = oldtail;
	q->tail = oldhead;
}

