#ifndef _hashset_h

#include <stdlib.h>

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

static int kExpansionFactor = 2;

hashset make_hashset(int default_capacity);

void free_hashset(hashset *h);

int contains(hashset *h, int item);

void insert(hashset *h, int item);

int hashset_remove(hashset *h, int item);

hashset intersect(hashset *h, hashset other);

hashset unify(hashset *h, hashset other);

int size(hashset *h);

#define _hashset_h
#endif