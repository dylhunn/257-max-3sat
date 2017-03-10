#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define kVarsPerClause 3

typedef struct formula {
	unsigned int num_vars;
	unsigned int num_clauses;
	int **clauses;
} formula;


/* Read a problem from a file using the DIMACS-CNF format.
 * Accepts a file path; returns 0 if successful and populates the provided formula.
 * Not thread-safe due to strtok.
 */
int read_input(char *file_path, formula *f);