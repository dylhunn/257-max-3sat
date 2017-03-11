#include "util.h"

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
	return 1;
}

int test_check_basic_solution() {
	formula f;
	int status = read_input("../test_data/test0.txt", &f);
	expect(status == 0);
	solution s1 = (int []) {0, 0, 0, 0, 1}; // good
	solution s2 = (int []) {1, 1, 1, 1, 1}; // good
	solution s3 = (int []) {0, 1, 0, 1, 1}; // bad
	expect(check_solution(f, s1));
	expect(check_solution(f, s2));
	expect(!check_solution(f, s3));
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
	test_wrapper("check_solution", test_check_basic_solution);

	printf("\n-----------------------\n");
	printf("| FINISHED TEST SUITE |\n");
	printf("-----------------------\n\n");
	return 0;
}