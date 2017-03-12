257-max-3sat | Dylan D. Hunn
============================


This is a collection of 3SAT solvers written in C, as part of my final project for Stanford **CS257 / Phil356C** (Logic and AI).

Fast start: skip to the "Building the project" section.

This project is still a work in progress.

Repo overview
=============

The source code for the project is stored in `/src`. Documentation for the code itself is contained in function comments of each header file.

The project report and slides (forthcoming) are stored, along with it's *LaTeX* source, in the `/report` folder.

Data files for testing are stored in the `/test-data` folder.

Project summary
===============

The purpose of this project is to better understand various algorithms for **3SAT** and **MAX-3SAT** by implementing them, and then by comparing them through benchmarking.

**3SAT** is a variant of the boolean satisfiability problem that requires formulae in conjunctive normal form, with three variables per clause. 3SAT is particularly useful as a "canonical" NP-Complete problem, and in practice, many hard problems are reduced to 3-CNF form as a preferred method of solving. 

Building the project
====================

You can build your own copy of the code by cloning the git repo, `cd`ing into the `src/` directory, and `make`ing the project.

Specifically:

    git clone https://github.com/dylhunn/257-max-3sat.git
    cd 257-max-3sat/src
    make test
will compile the project and run all tests to verify that it works. This was tested on Fedora 25, and should work on any modern Linux or Mac system. Windows users might have to change the line endings of the test data.
