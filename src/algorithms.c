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

