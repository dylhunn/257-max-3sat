#include "threesat.h"

#define kVarsPerClause 3

int read_input(char *file_path, formula *f) {
	FILE *fp;
	if ((fp = fopen(file_path, "r")) == 0) return (errno == 0) ? errno : -1;
	size_t line_length = 1;
	char *line = malloc(sizeof(char) * line_length); // will be resized by getline
	if (!line) return (errno == 0) ? errno : -1;
	*f = (formula) {.num_vars = -1, .num_clauses = -1, .clauses = 0};
	int curr_clause = 0;
	while ((getline(&line, &line_length, fp)) != -1) { // read each line in the file
		char *tok;
		if ((tok = strtok(line, " ")) == 0) continue; // empty line
		if (tok[0] == 'c') continue; // comment line
		if (tok[0] == 'p') { // problem definition line
			if ((tok = strtok(NULL, " ")) == 0) return -2; // missing data
			assert(strncmp(tok, "cnf", 3) == 0);
			if ((tok = strtok(NULL, " ")) == 0) return -2; // missing data
			f->num_vars = atoi(tok);
			if ((tok = strtok(NULL, " ")) == 0) return -2; // missing data
			f->num_clauses = atoi(tok);
			f->clauses = malloc(sizeof(int*) * f->num_clauses);
			if (!f->clauses) return (errno == 0) ? errno : -1;
			continue;
		}
		// clause definition line
		if (f->num_clauses == -1 || f->num_vars == -1) return -3; // not initialized
		if ((f->clauses[curr_clause] = malloc(sizeof(int) * kVarsPerClause)) == 0)
				return (errno == 0) ? errno : -1;
		for (int i = 0; i < kVarsPerClause; i++) { // read each variable in clause
			if (!tok) return -5; // not enough data
			f->clauses[curr_clause][i] = atoi(tok);
			tok = strtok(NULL, " "); 
		}
		if (tok != 0) return -4; // extra variables in clause
		curr_clause++;
    }
    free(line);
	fclose(fp);
	return 0;
}