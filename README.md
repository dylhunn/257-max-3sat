257-max-3sat | Dylan D. Hunn
============================


This is a collection of 3SAT solvers written in C, as part of my final project for Stanford **CS257 / Phil356C** (Logic and AI).

To get started immediately, skip to the "Building the project" section.

Repo overview
=============

The source code for the project is stored in `/src`. Documentation for the code itself is contained in function comments of each header file.

The project slides are stored in the `/slides` folder.

Data files for testing are stored in the `/test-data` folder.

Project summary
===============

The purpose of this project is to better understand various algorithms for **3SAT** and **MAX-3SAT** by implementing them, and then by comparing them to each other.

**3SAT** is a variant of the boolean satisfiability problem that requires formulae in conjunctive normal form, with three variables per clause. 3SAT is particularly useful as a "canonical" NP-Complete problem, and in practice, many hard problems are reduced to 3-CNF form as a preferred method of solving. 

##### Background and related work

Many competition-level 3SAT solvers exist. My goal with this project was to construct a "from-the-metal" implementation in C, in order to better understand how these solving algorithms work.

For an example of one such solver, you might looks at [a 3SAT project from UVA](http://www.cs.virginia.edu/~jwh6q/3sat-web/).


Building and running the project
================================

You can build your own copy of the code by cloning the git repo, `cd`ing into the `src/` directory, and `make`ing the project.

Specifically:

    git clone https://github.com/dylhunn/257-max-3sat.git
    cd 257-max-3sat/src
    make test
will compile the project and run all tests to verify that it works. This was tested on Fedora 25 and OS X 10.11, and should work on any modern Linux or Mac system. Windows users might have to change the line endings of the test data.

To run the 3SAT algorithms on arbitrary input files `cd` into `src/`, and run:

	make
    ./threesat ../test_data/test0.txt 0
where the first argument is the path to any valid DIMACS 3CNF file, and the second is the algorithm to run. Currently supported algorithms are:

Number | Algorithm
--- | ---
0 | Brute force exponential solver
1 | Bron-Kerbosch max-clique solver

Algorithms
==========

The **Brute force exponential solver**, as it sounds, tries every possible assignment of truth values to variables, checking them along the way, and terminates when it finds a valid assignment.

The **Bron-Kerbosch max-clique solver** first converts the formula into a graph, such that each term in a clause is a node, and all nodes are connected, with the exception of conflicting terms (*A ∧ ¬A*) and terms in the same clause. This graph is represented efficiently as an adjacency matrix. Then, it uses the [Bron-Kerbosch algorithm](https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm) to find max cliques; as soon as a max-clique with as many nodes as the total number of clauses is found, the solver halts, since this must be a satisfying assignment.

##### Relative efficiency

The naive-solver approach has exponential complexity, since it is a recursive algorithm with a branching factor of 2. 

The clique solver also has exponential complexity. However. in the worst case, no n-vertex graph has more than 3^(n/3) max-cliques. In practice, we can do even better: our nodes are connected to at most (n-4) other nodes, since no node is connected to the other nodes in its clause. Indeed, the difference is substantial, although not asymptotic:
![One exponential function grows more slowly.](http://i.imgur.com/qiGZl8P.png "One exponential function grows more slowly.")

Other packaged code
===================

This project also includes a custom hashset implementation, which is an efficient chaining hashset for integers that provides iterators. This allows simpler hash function behavior (the identity function, since the key space is evenly distributed integer indices from the adjacency matrix) and removes reliance on external dependencies.

Additionally, a custom C test harness is present, to which new test cases can be easily added.

##### Why a custom hashset
The hashset is being used for the Bron-Kerbosh algorithm, to store nodes from the adjacency matrix. Since each node is represented as an index into the matrix, we expect uniformly distributed integer keys; thus, the identity function will suffice as a hash. Moreover, since we are only storing integers, no genericization is necessary. Both of these provide efficiency boosts. Moreover, the inclusion of the hashset allows the code to be modular, with no external dependencies.

License
=======

This code is free software available under the [GPL v3](https://www.gnu.org/licenses/gpl-3.0.en.html) or newer, as published by the Free Software Foundation.