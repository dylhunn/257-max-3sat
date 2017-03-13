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
 * vertexes.
 */
hashset get_neighbor_set(int **adjacency_matrix, int num_vertexes, int vertex_index) {
	hashset neighbors = hashset_make(10);
	for (int i = 0; i < num_vertexes; i++) {
		if (adjacency_matrix[vertex_index][i]) hashset_insert(&neighbors, i);
	}
	return neighbors;
}

hashset bron_kerbosch_helper(hashset r, hashset p, hashset x) {
	if (hashset_size(&p) == 0 && hashset_size(&x) == 0) {

	}
}

/* The Bron-Kerbosch algorithm is an efficient method of finding max-cliques.
 */
hashset bron_kerbosch_search() {

}

solution max_clique_solve(const formula f) {
	solution s = malloc(sizeof(int) * f.num_vars);
	int num_terms = f.num_clauses * kVarsPerClause;
	int **compatible = generate_clique_adjacency_matrix(f);
	
	// if an assignment exists, it is a max-clique with size num_clauses!


	free_clique_adjacency_matrix(compatible, num_terms);
	return s;
}

