#include <signal.h>
#include "algorithms.h"
#include "util.h"

// output colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define expect(x) if ((x) == 0) {printf(RED "line %d (%s) " RESET, \
	(__LINE__), (__FILE__)); return 0;}

// Gracefully print our own error message upon fatal errors.
void sig_handler(int sig_num) {
	printf(RED " (fatal signal intercepted)\n" RESET);
	exit(1);
}

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
	// solvable
	char *file_paths[] = 
		{"../test_data/test0.txt", "../test_data/test1.txt"};
	for (int i = 0; i < 2; i++) {
		int status = read_input(file_paths[i], &f);
		expect(status == 0);
		solution s = naive_solve(f);
		expect(check_solution(f, s));
		free_formula(f);
		free(s);
	}
	//unsolvable
	char *file_paths2[] = {"../test_data/unsolvable.txt"};
	for (int i = 0; i < 1; i++) {
		int status = read_input(file_paths2[i], &f);
		expect(status == 0);
		solution s = naive_solve(f);
		expect(s == NULL);
		expect(!check_solution(f, s));
		free_formula(f);
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
	// Handle fatal signals to print failure message gracefully.
	signal(SIGSEGV, sig_handler);
	signal(SIGFPE, sig_handler);
	signal(SIGILL, sig_handler);
	signal(SIGBUS, sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGIOT, sig_handler);
	signal(SIGSYS, sig_handler);

	printf("-----------------------\n");
	printf("| STARTING TEST SUITE |\n");
	printf("-----------------------\n");
	printf(CYN "This suite checks that the code compiles and runs as "
		"expected on your system." RESET);
	test_wrapper("file reading", test_read_basic_file);
	test_wrapper("file reading with error (too many vars in clause)",
		test_too_many_vars);
	test_wrapper("basic solution checking", test_check_basic_solutions);
	test_wrapper("naive 3sat solver", test_naive_solve);
	printf("\n-----------------------\n");
	printf("| FINISHED TEST SUITE |\n");
	printf("-----------------------\n\n");
	return 0;
}