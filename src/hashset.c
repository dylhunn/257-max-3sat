#include "hashset.h"

int hash(hashset *h, int item) {
	return item % h->backing_size; // trivial identity hash
}

hashset hashset_make(int default_capacity) {
	// remember to memset to 0
	hashset new_hashset;
	new_hashset.data = malloc(sizeof(hash_node*) * default_capacity);
	for (int i = 0; i < default_capacity; i++) new_hashset.data[i] = 0;
	new_hashset.count = 0;
	new_hashset.backing_size = default_capacity;
	new_hashset.iter_previously_found_node = NULL;
	new_hashset.previously_found_node_bucket = -1;
	new_hashset.p_iter_previously_found_node = NULL;
	new_hashset.p_previously_found_node_bucket = -1;
	return new_hashset;
}

void hashset_free(hashset *h) {
	// TODO
}

void hashset_expand(hashset *h) {
	hashset new_set = hashset_make(h->backing_size * kExpansionFactor);
	for (int i = 0; i < h->backing_size; i++) {
		hash_node *next_node = h->data[i];
		while (next_node != NULL) {
			hashset_insert(&new_set, next_node->element);
			next_node = next_node->next;
		}
	}
	hashset_free(h);
	h->data = new_set.data;
	h->count = new_set.count;
	h->backing_size = new_set.backing_size;
}

int hashset_contains(hashset *h, int item) {
	int bucket = hash(h, item);
	if (h->data[bucket] == NULL) return 0;
	hash_node *existing_node = h->data[bucket];
	while (existing_node->next != NULL) {
		if (existing_node->element == item) return 1;
		existing_node = existing_node->next;
	}
	return (existing_node->element == item); // last item
}

int hashset_insert(hashset *h, int item) {
	if (hashset_contains(h, item)) return 0;
	if (h->backing_size <= h->count + 1) hashset_expand(h);
	h->count++;
	hash_node *new_node = malloc(sizeof(hash_node));
	new_node->element = item;
	new_node->next = NULL;
	int bucket = hash(h, item);
	if (h->data[bucket] == NULL) {
		h->data[bucket] = new_node;
		return 1;
	}
	// append to list
	hash_node *existing_node = h->data[bucket];
	while (existing_node->next != NULL) {
		existing_node = existing_node->next;
	}
	existing_node->next = new_node;
	return 1;
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

hashset hashset_intersect(hashset *h, hashset *other) {
	hashset new_set = hashset_make(h->backing_size); // TODO better guess
	for (int i = 0; i < other->backing_size; i++) {
		hash_node *next_node = other->data[i];
		while (next_node != NULL) {
			if (hashset_contains(h, next_node->element)) {
				hashset_insert(&new_set, next_node->element);
			}
			next_node = next_node->next;
		}
	}
	return new_set;
}

hashset hashset_unify(hashset *h, hashset *other) {
	hashset new_set = hashset_make((hashset_size(h) + hashset_size(other))
		* kExpansionFactor);
	for (int i = 0; i < h->backing_size; i++) {
		hash_node *next_node = h->data[i];
		while (next_node != NULL) {
			hashset_insert(&new_set, next_node->element);
			next_node = next_node->next;
		}
	}
	for (int i = 0; i < other->backing_size; i++) {
		hash_node *next_node = other->data[i];
		while (next_node != NULL) {
			hashset_insert(&new_set, next_node->element);
			next_node = next_node->next;
		}
	}
	return new_set;
}

int hashset_size(hashset *h) {
	return h->count;
}

void hashset_print(hashset *h) {
	for (int i = 0; i < h->backing_size; i++) {
		hash_node *next_node = h->data[i];
		while (next_node != NULL) {
			printf("%d, ", next_node->element);
			next_node = next_node->next;
		}
	}
	printf("\n");
}

hashset hashset_copy(hashset *h) {
	hashset newh = hashset_make(10);
	for (int i = 0; i < h->backing_size; i++) {
		hash_node *next_node = h->data[i];
		while (next_node != NULL) {
			hashset_insert(&newh, next_node->element);
			next_node = next_node->next;
		}
	}
	return newh;
}

int hashset_iter_first(hashset *iter_h) {
	iter_h->iter_previously_found_node = NULL;
	iter_h->previously_found_node_bucket = -1;
	iter_h->p_iter_previously_found_node = NULL;
	iter_h->p_previously_found_node_bucket = -1;
	
	for (int i = 0; i < iter_h->backing_size; i++) {
		hash_node *curr_node = iter_h->data[i];
		if (curr_node == NULL) continue;
		iter_h->previously_found_node_bucket = i;
		iter_h->iter_previously_found_node = curr_node;
		return curr_node->element;
	} 
	return INT_MIN;
}

int hashset_iter_next(hashset *iter_h) {
	// The first node might have been removed
	if (iter_h->iter_previously_found_node == NULL) {
		return hashset_iter_first(iter_h);
	}

	hash_node *next_node = iter_h->iter_previously_found_node->next;
	if (next_node != NULL) {
		iter_h->p_iter_previously_found_node = iter_h->iter_previously_found_node;
		iter_h->iter_previously_found_node = next_node;
		return next_node->element;
	}

	int next_bucket = iter_h->previously_found_node_bucket + 1;
	for (int i = next_bucket; i < iter_h->backing_size; i++) {
		hash_node *curr_node = iter_h->data[i];
		if (curr_node == NULL) continue;
		iter_h->p_iter_previously_found_node = iter_h->iter_previously_found_node;
		iter_h->iter_previously_found_node = curr_node;
		iter_h->p_previously_found_node_bucket = iter_h->previously_found_node_bucket;
		iter_h->previously_found_node_bucket = i;
		return curr_node->element;
	}
	return INT_MIN;
}

void hashset_iter_remove(hashset *iter_h) {
	if (iter_h->previously_found_node_bucket == -1 ||
		iter_h->iter_previously_found_node == NULL) {
			printf("(iterator_exception)");
			exit(1);
	}
	hashset_remove(iter_h, iter_h->iter_previously_found_node->element);
	iter_h->previously_found_node_bucket = iter_h->p_previously_found_node_bucket;
	iter_h->iter_previously_found_node = iter_h->p_iter_previously_found_node;
}