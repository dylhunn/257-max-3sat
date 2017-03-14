#ifndef _util_h

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#define kVarsPerClause 3

// output colors
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct formula {
	int num_vars;
	int num_clauses;
	int **clauses;
} formula;

/* A solution is an array of bools (ints)
 * a NULL solution means no solution is possible.
 */
typedef int *solution;

/* Read a problem from a file using the DIMACS-CNF format.
 * Accepts a file path; returns 0 if successful and populates the provided formula.
 * Not thread-safe due to strtok.
 * Allocates data in the formula; must be freed with free_formula().
 */
int read_input(const char *file_path, formula *f);

/* Accept a solution and a 3SAT formula, and see if the solution satisfies the
 * formula.
 */
int check_solution(const formula f, const solution s);

/* Free the memory allocated for clauses in a formula.
 */
void free_formula(formula f);

/* Print a solution array.
*/
void print_solution(solution s, int l);

#define _util_h
#endif