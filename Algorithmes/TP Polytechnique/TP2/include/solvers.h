#ifndef SOLVERS_H
#define SOLVERS_H

#include <string>

// Typedef of a solver of our problem
typedef int(*solver)(int*, int, int, int, bool);

// The solvers
int greedy_solver(int* v, int n, int c, int m, bool print_solution = false);
int dynamic_programming_solver(int* v, int n, int c, int m, bool print_solution = false);
int simulated_annealing_solver(int* v, int n, int c, int m, bool print_solution = false);

static std::string solvers_names[3] = {"greedy solver", "dynamic programming solver", "simulated annealing solver"};
static solver solvers[3] = {greedy_solver, dynamic_programming_solver, simulated_annealing_solver};

int get_solver_used();

#endif // SOLVERS_H