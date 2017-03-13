#include "algorithms.h"

int naive_helper(const formula f, solution s, int index) {
	if (index >= f.num_vars) {
		if (check_solution(f, s)) return 1;
		return 0;
	}
	for (int i = 0; i < 2; i++) {
		s[index] = i;
		if (naive_helper(f, s, index + 1)) return 1;
	}
	return 0;
}

solution naive_solve(const formula f) {
	solution s = malloc(sizeof(int) * f.num_vars);
	int solution_found = naive_helper(f, s, 0);
	if (!solution_found) {
		free(s);
		s = NULL;
	}
	return s;
}

int **generate_clique_adjacency_matrix(const formula f) {
	int num_terms = f.num_clauses * kVarsPerClause;

	// construct a 2D array of appropriate size
	int **compatible = malloc(sizeof(int*) * num_terms);
	for (int i = 0; i < num_terms; i++) {
		compatible[i] = malloc(sizeof(int) * num_terms);
		// initialize every cell to 0
		for (int j = 0; j < num_terms; j++) {
			compatible[i][j] = 0;
		}
	}

	// for every pairing of terms, determine if they are compatible
	for (int i = 0; i < num_terms; i++) {
		for (int j = i + 1; j < num_terms; j++) {
			// skip j if it's in the same clause as i; not compatible
			if (i / 3 == j / 3) continue;
			// incompatible if one variable is a negation of the other
			if (f.clauses[i/3][i%3] == -f.clauses[j/3][j%3]) continue;
			// otherwise, compatible
			compatible[i][j] = compatible[j][i] = 1;
		}
	}

	return compatible;
}

void free_clique_adjacency_matrix(int **matrix, int size) {
	// free the arrays
	for (int i = 0; i < size; i++) {
		free(matrix[i]);
	}
	free(matrix);
}

/* Accepts a graph encoded as an adjacency matrix, and a vertex, as specified
 * by its index in the matrix. Returns a set of the indices of all adjacent
 * vertexes. Caller must free the neighbor set.
 */
hashset get_neighbor_set(int **adjacency_matrix, int num_vertexes, int vertex_index) {
	hashset neighbors = hashset_make(10);
	for (int i = 0; i < num_vertexes; i++) {
		if (adjacency_matrix[vertex_index][i]) hashset_insert(&neighbors, i);
	}
	return neighbors;
}

/* Find a max-clique of size n (required_size).
 * Accepts three populated hashsets r, p, and x, and the required size (n).
 * Also requires the graph to be passed in as a parameter.
 * Returns 1 if a solution was found, and 0 if no solution was found.
 * The solution will be stored in r.
 */
int bron_kerbosch_find_nclique(hashset *r, hashset *p, hashset *x, int required_size,
	int **adjacency_matrix, int num_vertexes) {
		if (hashset_size(p) == 0 && hashset_size(x) == 0
			&& hashset_size(r) == required_size) {
				return 1;
		}
		if (hashset_size(p) == 0) return 0; // the search cannot continue
		for (int v = hashset_iter_first(p); v != INT_MIN; v = hashset_iter_next(p)) {
				int inserted = hashset_insert(r, v);
				hashset neighbors_of_v = get_neighbor_set(adjacency_matrix, num_vertexes, v);
				hashset p_insersect_n_of_v = hashset_intersect(p, &neighbors_of_v);
				hashset x_insersect_n_of_v = hashset_intersect(x, &neighbors_of_v);
				if (bron_kerbosch_find_nclique(r, &p_insersect_n_of_v,
					&x_insersect_n_of_v, required_size, adjacency_matrix, num_vertexes)) {
						hashset_free(&neighbors_of_v);
						hashset_free(&p_insersect_n_of_v);
						hashset_free(&x_insersect_n_of_v);
						hashset_free(p);
						return 1;
				}
				if (inserted) hashset_remove(r, v);
				hashset_iter_remove(p); // remove v
				hashset_insert(x, v);
				hashset_free(&neighbors_of_v);
				hashset_free(&p_insersect_n_of_v);
				hashset_free(&x_insersect_n_of_v);
		}
		return 0;
}

solution max_clique_solve(const formula f) {
	solution s = malloc(sizeof(int) * f.num_vars);
	int num_terms = f.num_clauses * kVarsPerClause; // also num_vertices
	int **compatible = generate_clique_adjacency_matrix(f);
	
	hashset vertex_set = hashset_make(num_terms);
	for (int i = 0; i < num_terms; i++) {
		hashset_insert(&vertex_set, i);
	}
	hashset r = hashset_make(num_terms);
	hashset x = hashset_make(num_terms);

	int result = bron_kerbosch_find_nclique(&r, &vertex_set, &x,
		f.num_clauses, compatible, num_terms);

	hashset assignments = hashset_make(num_terms);
	// for every vertex in the result clique

	if (result == 0) { // no solution
		free(s);
		s = NULL;
		goto free_memory;
	}

	for (int vertexid = hashset_iter_first(&r); vertexid != INT_MIN;
		vertexid = hashset_iter_next(&r)) {
			hashset_insert(&assignments, vertexid);
	}

	for (int i = 0; i < f.num_vars; i++) {
		if (hashset_contains(&assignments, i)) s[i] = 1;
		else s[i] = 0;
	}

	free_memory:
	hashset_free(&assignments);
	hashset_free(&r);
	hashset_free(&x);
	hashset_free(&vertex_set);
	free_clique_adjacency_matrix(compatible, num_terms);
	return s;
}

