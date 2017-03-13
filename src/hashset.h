#ifndef _hashset_h

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

// internal use
typedef struct hash_node {
	struct hash_node *next;
	int element;
} hash_node;

typedef struct hashset {
	hash_node **data; // array of pointers to nodes; internal use
	int count; // actual "size"
	int backing_size; // internal use
	int previously_found_node_bucket; // internal use
	hash_node *iter_previously_found_node; // internal use
	int p_previously_found_node_bucket; // internal use
	hash_node *p_iter_previously_found_node; // internal use
} hashset;

static const int kExpansionFactor = 2;

hashset hashset_make(int default_capacity);

void hashset_free(hashset *h);

int hashset_contains(hashset *h, int item);

int hashset_insert(hashset *h, int item);

int hashset_remove(hashset *h, int item);

hashset hashset_intersect(hashset *h, hashset *other);

hashset hashset_unify(hashset *h, hashset *other);

int hashset_size(hashset *h);

void hashset_print(hashset *h);

hashset hashset_copy(hashset *h);

/* first() and next() will return INT_MIN if no more elements exist.
 * Calling insert() or remove() while iterating has undefined behavior;
 * use the iter_remove() instead.
 * Nested iteration on the same set not currently supported.
 */
int hashset_iter_first(hashset *iter_h);

int hashset_iter_next(hashset *iter_h);

void hashset_iter_remove(hashset *iter_h);

#define _hashset_h
#endif