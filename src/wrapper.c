#include "util.h"
#include "algorithms.h"

void solve(char *path, solution (*f)(const formula f)) {
	formula frm;
	int success = read_input(path, &frm);
	if (success != 0) {
		printf(RED " Bad input file.\n" RESET);
		exit(1);
	}
	solution sol = f(frm);
	if (sol == NULL ) {
		printf(MAG "No solution is possible.\n" RESET);
		exit(0);
	}
	printf(GRN "Solvable. Solution: [");
	for (int i = 0; i < frm.num_vars; i++) {
		printf("var%d=", i+1);
		(sol[i]) ? printf("true") : printf("false");
		if (i < frm.num_vars - 1) printf(", ");
	}
	printf("]\n" RESET);
	free(sol);
	free_formula(frm);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf(RED "Incorrect number of arguments supplied.\nSpecify the DIMACS 3CNF problem file, and the algorithm number.\n" RESET);
		exit(1);
	}
	switch(atoi(argv[2])) {
		case 0: solve(argv[1], naive_solve);
		break;
		case 1: solve(argv[1], max_clique_solve);
		break;
		default:
		printf(RED "Invalid algorithm number.\n" RESET);
		exit(1);
	}
	return 0;
}