#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

// The solver
//double solver(int employees, const std::vector<std::vector<int>>& zoo, std::vector<std::vector<std::vector<int>>>& solution);
double simplified_variance(const std::vector<int>& v);
double step_1_solver(int employees, const std::vector<std::vector<int>>& zoo, std::vector<int>& solution);
double step_2_solver(int employees_in_zone, const std::vector<int>& zone, std::vector<std::vector<int>>& solution);


#endif // SOLVER_H