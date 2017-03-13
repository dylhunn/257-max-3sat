#ifndef _hashset_h

#include <stdlib.h>
#include <stdio.h>

// internal use
typedef struct hash_node {
	struct hash_node *next;
	int element;
} hash_node;

typedef struct hashset {
	hash_node **data; // array of pointers to nodes; internal use
	int count; // actual "size"
	int backing_size; // internal use
} hashset;

static const int kExpansionFactor = 2;

hashset hashset_make(int default_capacity);

void hashset_free(hashset *h);

int hashset_contains(hashset *h, int item);

void hashset_insert(hashset *h, int item);

int hashset_remove(hashset *h, int item);

hashset hashset_intersect(hashset *h, hashset *other);

hashset hashset_unify(hashset *h, hashset *other);

int hashset_size(hashset *h);

void hashset_print(hashset *h);

/* Hashset iterator support
 * Modifying the set between calling first() and next() or hasnext() has
 * undefined behavior.
 */
int hashset_iter_first(hashset *h);

int hashset_iter_next();

int hashset_iter_hasnext();


#define _hashset_h
#endif