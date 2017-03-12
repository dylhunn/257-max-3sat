#include "hashset.h"

int hash(hashset *h, int item) {
	return item % h->backing_size; // trivial identity hash
}

hashset make_hashset(int default_capacity) {
	// remember to memset to 0
	hashset new_hashset;
	new_hashset.data = malloc(sizeof(hash_node*) * default_capacity);
	for (int i = 0; i < default_capacity; i++) new_hashset.data[i] = 0;
	new_hashset.count = 0;
	new_hashset.backing_size = default_capacity;
	return new_hashset;
}

void free_hashset(hashset *h) {
	// TODO
}

void expand_hashset(hashset *h) {
	hashset new_set = make_hashset(h->backing_size * kExpansionFactor);
	for (int i = 0; i < h->backing_size; i++) {
		hash_node *next_node = h->data[i];
		while (next_node != NULL) {
			insert(&new_set, next_node->element);
			next_node = next_node->next;
		}
	}
	free_hashset(h);
	h->data = new_set.data;
	h->count = new_set.count;
	h->backing_size = new_set.backing_size;
}

int contains(hashset *h, int item) {
	int bucket = hash(h, item);
	if (h->data[bucket] == NULL) return 0;
	hash_node *existing_node = h->data[bucket];
	while (existing_node->next != NULL) {
		if (existing_node->element == item) return 1;
		existing_node = existing_node->next;
	}
	return (existing_node->element == item); // last item
}

void insert(hashset *h, int item) {
	if (contains(h, item)) return;
	if (h->backing_size >= h->count - 1) expand_hashset(h);
	h->count++;
	hash_node *new_node = malloc(sizeof(hash_node));
	new_node->element = item;
	new_node->next = NULL;
	int bucket = hash(h, item);
	if (h->data[bucket] == NULL) {
		h->data[bucket] = new_node;
		return;
	}
	// append to list
	hash_node *existing_node = h->data[bucket];
	while (existing_node->next != NULL) {
		existing_node = existing_node->next;
	}
	existing_node->next = new_node;
}

int hashset_remove(hashset *h, int item) {
	int bucket = hash(h, item);
	if (h->data[bucket] == NULL) return 0; // no items
	if (h->data[bucket]->element == item) { // first element
		hash_node *to_remove = h->data[bucket];
		h->data[bucket] = h->data[bucket]->next;
		free(to_remove);
		h->count--;
		return 1;
	}
	hash_node *curr = h->data[bucket];
	while (curr->next != NULL) { // non-first element
		if (curr->next->element == item) {
			hash_node *to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove);
			h->count--;
			return 1;
		}
	}
	return 0;
}

hashset intersect(hashset *h, hashset other) {
	
}

hashset unify(hashset *h, hashset other) {

}

int size(hashset *h) {
	return h->count;
}