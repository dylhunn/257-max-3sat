#include "util.h"
#include "algorithms.h"

// output colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"

#define expect(x) if ((x) == 0) {printf(RED "line %d (%s) " RESET, \
	(__LINE__), (__FILE__)); return 0;}


int test_read_basic_file() {
	formula f;
	int status = read_input("../test_data/test0.txt", &f);
	expect(status == 0);
	expect(f.num_vars == 5);
	expect(f.num_clauses == 2);
	expect(f.clauses[0][0] == 1);
	expect(f.clauses[0][1] == -2);
	expect(f.clauses[0][2] == 3);
	expect(f.clauses[1][0] == 4);
	expect(f.clauses[1][1] == 2);
	expect(f.clauses[1][2] == 5);
	free_formula(f);
	return 1;
}

int test_check_basic_solutions() {
	formula f;
	int status = read_input("../test_data/test0.txt", &f);
	expect(status == 0);
	solution s1 = (int []) {0, 0, 0, 0, 1}; // good
	solution s2 = (int []) {1, 1, 1, 1, 1}; // good
	solution s3 = (int []) {0, 1, 0, 1, 1}; // bad
	expect(check_solution(f, s1));
	expect(check_solution(f, s2));
	expect(!check_solution(f, s3));
	free_formula(f);
	status = read_input("../test_data/test1.txt", &f);
	expect(status == 0);
	solution s4 = (int []) {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0}; // bad
	solution s5 = (int []) {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1}; // bad
	solution s6 = (int []) {1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1}; // good
	expect(!check_solution(f, s4));
	expect(!check_solution(f, s5));
	expect(check_solution(f, s6));
	free_formula(f);
	return 1;
}

int test_naive_solve() {
	formula f;
	const char * const file_paths[] = 
		{"../test_data/test0.txt", "../test_data/test1.txt"};
	for (int i = 0; i < 2; i++) {
		int status = read_input(file_paths[i], &f);
		expect(status == 0);
		solution s = naive_solve(f);
		expect(check_solution(f, s));
		free_formula(f);
		free(s);
	}
	return 1;
}

int test_too_many_vars() {
	formula f;
	int status = read_input("../test_data/testTooManyVarsInClause.txt", &f);
	expect(status != 0);
	return 1;
}

void test_wrapper(char *test_name, int (*f)(void)) {
	printf("\nTesting %s... ", test_name);
	int status = (*f)();
	if (status) printf(GRN "passed." RESET);
	else printf(RED "failed; test aborted." RESET);
}

int main() {
	printf("-----------------------\n");
	printf("| STARTING TEST SUITE |\n");
	printf("-----------------------");

	test_wrapper("file reading", test_read_basic_file);
	test_wrapper("too many vars in clause", test_too_many_vars);
	test_wrapper("basic solution checking", test_check_basic_solutions);
	test_wrapper("naive solver", test_naive_solve);

	printf("\n-----------------------\n");
	printf("| FINISHED TEST SUITE |\n");
	printf("-----------------------\n\n");
	return 0;
}