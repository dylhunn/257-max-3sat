#ifndef _algorithms

#include "util.h"

/* Solves a provided formula. Caller must free the returned solution, if one is found.
 * Uses a trivial and inefficient algorithm that "brute-forces" every possible
 * assignment, until a successful one is found.
 */
solution naive_solve(const formula f);

#define _algorithms
#endif