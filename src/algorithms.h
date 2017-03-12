#ifndef _algorithms

#include "util.h"

/* Solves a provided formula. Caller must free the returned solution, if one is found.
 * Returns NULL if no solution is found.
 * Uses a trivial and inefficient algorithm that "brute-forces" every possible
 * assignment, until a successful one is found.
 */
solution naive_solve(const formula f);

/* Solves a provided formula. Caller must free the returned solution, if one is found.
 * Returns NULL if no solution is found.
 * Converts the 3SAT instance into a graph, and solves the max-clique problem
 * to find a valid assignment using the Bron-Kerbosch algorithm.
 */
solution max_clique_solve(const formula f);

#define _algorithms
#endif