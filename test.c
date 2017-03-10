#include "threesat.h"

#define expect(x) if ((x) == 0) return 0;

#define RED   "\x1B[31m"
#define RESET "\x1B[0m"

int test_read_basic_file() {
	formula f;
	int status = read_input("data/test0.txt", &f);
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

int test_too_many_vars() {
	formula f;
	int status = read_input("data/testTooManyVarsInClause.txt", &f);
	expect(status != 0);
	return 1;
}

void test_wrapper(char *test_name, int (*f)(void)) {
	printf("Testing %s... ", test_name);
	int status = (*f)();
	if (status) printf("done.\n");
	else printf(RED "failed.\n" RESET);
}

int main() {
	printf("\n-----------------------\n");
	printf("| STARTING TEST SUITE |\n");
	printf("-----------------------\n");

	test_wrapper("file reading", test_read_basic_file);
	test_wrapper("too many vars in clause", test_too_many_vars);

	printf("\n-----------------------\n");
	printf("| FINISHED TEST SUITE |\n");
	printf("-----------------------\n\n");
	return 0;
}