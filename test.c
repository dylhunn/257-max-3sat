#include "threesat.h"

void test_read_file() {
	formula f;
	int status = read_input("data/test0.txt", &f);
	assert(status == 0);
	assert(f.num_vars == 5);
	assert(f.num_clauses == 2);
	assert(f.clauses[0][0] == 1);
	assert(f.clauses[0][1] == -2);
	assert(f.clauses[0][2] == 3);
	assert(f.clauses[1][0] == 4);
	assert(f.clauses[1][1] == 2);
	assert(f.clauses[1][2] == 5);
}

void test_wrapper(char *test_name, void (*f)(void)) {
	printf("Testing %s... ", test_name);
	(*f)();
	printf("done.\n");
}

int main() {
	printf("\n-----------------------\n");
	printf("| STARTING TEST SUITE |\n");
	printf("-----------------------\n");

	test_wrapper("file reading", test_read_file);

	printf("\n-----------------------\n");
	printf("| FINISHED TEST SUITE |\n");
	printf("-----------------------\n\n");
	return 0;
}