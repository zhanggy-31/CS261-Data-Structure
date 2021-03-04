/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:Guangyu Zhang
 * Email:zhangg3@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"
#include "assert.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct pq{
    struct dynarray* dyn;
};

struct node{
    int priority;
    void* data;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
    struct pq* pq = malloc(sizeof(struct pq));
    assert(pq);
    pq->dyn = dynarray_create();
  return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
    assert(pq);
    if(pq_isempty(pq) == 0){
        pq_remove_first(pq);
    }
    dynarray_free(pq->dyn);
    free(pq);
  return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
    assert(pq);
    if(dynarray_size(pq->dyn) == 0){
        return 1;
    }
    else{
        return 0;
    }
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
    assert(pq);
    struct node* new = malloc(sizeof(struct node));
    new->data = value;
    new->priority = priority;
    dynarray_insert(pq->dyn, new);

    int cur_index = dynarray_size(pq->dyn) - 1;
    int par_index = 0;
    struct node *temp;

    while(par_index >= 0){
        par_index = (cur_index - 1)/2;
        temp = dynarray_get(pq->dyn, par_index);

        if(temp->priority > new->priority){
            dynarray_set(pq->dyn, par_index, new);
            dynarray_set(pq->dyn, cur_index, temp);
            cur_index = par_index;
        }
        else{
            break;
        }
    }
  temp = NULL;
  return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
    assert(pq);
    assert(dynarray_size(pq->dyn) > 0);
    struct node* first = NULL;
    first = dynarray_get(pq->dyn, 0);
  return first->data;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
    assert(pq);
    assert(dynarray_size(pq->dyn) > 0);
    struct node* first = NULL;
    first = dynarray_get(pq->dyn, 0);
  return first->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
    assert(pq);
    struct node* firstelem = NULL;
    struct node* lastelem = NULL;

    firstelem = (struct node*)dynarray_get(pq->dyn, 0);
    lastelem = (struct node*)dynarray_get(pq->dyn, dynarray_size(pq->dyn) - 1);
    dynarray_set(pq->dyn, 0, lastelem);
    dynarray_remove(pq->dyn, dynarray_size(pq->dyn) - 1);
    lastelem = NULL;

    int elem = 0;
    int lChild = 0;
    int rChild = 0;
    int minChild = 0;
    struct node* tmp1;
    struct node* tmp2;

    while (1) {
        lChild = (2 * elem) + 1;
        rChild = (2 * elem) + 2;

        if(((2 * elem) + 1) > dynarray_size(pq->dyn) - 1){
            break;
        }
        else if(lChild == dynarray_size(pq->dyn) - 1){
            minChild = lChild;
        }
        else{
            if (((struct node*)dynarray_get(pq->dyn, lChild)) -> priority <= ((struct node*)dynarray_get(pq->dyn, rChild))->priority){
                minChild = lChild;
            }
            else{
                minChild = rChild;
            }
        }

        if((((struct node*)dynarray_get(pq->dyn, elem))->priority) > (((struct node*)dynarray_get(pq->dyn, minChild))->priority)){
            tmp1 = (struct node*)dynarray_get(pq->dyn, minChild);
            tmp2 = (struct node*)dynarray_get(pq->dyn, elem);
            dynarray_set(pq->dyn, minChild, tmp2);
            dynarray_set(pq->dyn, elem, tmp1);
            elem = minChild;
        }
        else
            break;
    }

    if(firstelem != NULL){
        void *data = firstelem-> data;
        free(firstelem);
        return data;
    }

    else{
        return NULL;
    }
}
