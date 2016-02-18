#include "solver.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

using namespace std;


/*****************************************
 *             - UTILITIES -             *
 *	     USEFUL TYPES AND FUNCTIONS		 *
 *****************************************/

// Functor : compares pair by second member
class ComparePairBySecondMember {
	public:
		template<typename T, typename S>
		bool operator() (const pair<T, S>& p1, const pair<T, S>& p2) const {
			return p1.second < p2.second;
		}
};

// Calculates n*variance of a vector
double simplified_variance(const vector<int>& v) {
	double mean = ((double)accumulate(v.begin(), v.end(), 0.0)) / v.size();
	double res = 0.0;
	for (int i = 0; i < v.size(); i++) {
		res += (v[i] - mean)*(v[i] - mean);
	}
	return res;
}

// Metropolis criteria for simulated annealing
bool metropolis_criteria(int delta, double theta) {
	return (delta >= 0 || exp(delta/theta) >= (rand() / (double)(RAND_MAX)));
}

/*****************************************
 *              - STEP 1 -               *
 *            GREEDY SOLVER              *
 *****************************************/

double step_1_solver(int employees, const vector<vector<int>>& zoo, vector<int>& solution) {
	int zones = zoo.size(); // The number of zones
	priority_queue<pair<int, double>, vector<pair<int, double>>, ComparePairBySecondMember> greedy_values; // The values that we want to minimize (increment heuristic)
	vector<int> sum(zones, 0); // The sum of the animal values in each zone
	int current_employees = zones; // The number of employees currently assigned by the greedy algorithm
	double res = 0.0; // The final minimized value

	// Init :  
	// Each zone gets one employee
	// Computing the sum of the values of the animals in each zone
	// Computing the first greedy values
	for (int i = 0; i < zones; i++) {
		solution.push_back(1);
		for (int animal_value : zoo[i]) {
			sum[i] += animal_value;
		}
		greedy_values.push(pair<int,double>(i, sum[i]*sum[i]/2.0));
	}

	// Greedy loop : computing the solution while we can still add employees
	while (current_employees < employees) {
		int minimizing_zone = greedy_values.top().first; // The zone where the greedy value is minimum

		while (solution[minimizing_zone] >= zoo[minimizing_zone].size()) {
			greedy_values.pop();
			minimizing_zone = greedy_values.top().first;
		}

		solution[minimizing_zone] += 1; // Adding an employee to this zone
		
		// Updating the value of this zone
		greedy_values.pop();
		greedy_values.push(pair<int,double>(minimizing_zone, (sum[minimizing_zone])*(sum[minimizing_zone])*(1.0/solution[minimizing_zone] - 1.0/(solution[minimizing_zone] + 1))));
		
		// Updating the number of employees
		current_employees += 1;
	}

	for (int i = 0; i < zones; i++) {
		res += sum[i]*sum[i]/((double)solution[i]);
	}

	return res;
}

/*****************************************
 *   	        - STEP 2 -				 *
 *      SIMULATED ANNEALING SOLVER       *
 *****************************************/

double simulated_annealing_solver(int employees_in_zone, const vector<int>& zone, vector<vector<int>>& solution, int k_max, double t, int p, double alpha) {
	vector<vector<int>> current_solution(employees_in_zone);
	vector<int> current_solution_sum(employees_in_zone);
	double simplified_variance_solution, simplified_variance_current_solution;

	// Trivial case : only one employee in the zone
	if (employees_in_zone == 1) {
		for (int i = 0; i < zone.size(); i++) {
			solution[0].push_back(zone[i]);
		}
		return simplified_variance(solution[0]);
	}

	// Each employee gets an animal
	for (int i = 0; i < zone.size(); i++) {
		int j = i;
		if (i >= employees_in_zone) {
			j = rand()%employees_in_zone;
		}
		solution[j].push_back(zone[i]);
		current_solution[j].push_back(zone[i]);
		current_solution_sum[j] += zone[i];
	}

	// Other trival case : there are the same number of employees than animals
	if (employees_in_zone == zone.size()) {
		return simplified_variance(zone);
	}

	// Init the variance of the solution
	simplified_variance_solution = simplified_variance(current_solution_sum);

	// Init the variance of the current solution
	simplified_variance_current_solution = simplified_variance_solution;

	for (int k = 0; k < k_max; k++) {
		for (int j = 0; j < p; j++) {
			vector<vector<int>> attempt(current_solution);
			vector<int> attempt_sum(current_solution_sum);
			double simplified_variance_attempt;
			// Generating a new attempt
			// We choose an employee at random
			// We choose at random the number of animals we'll take away from him
			int employee_helped = rand()%employees_in_zone;
			int number_of_animals_taken = 1 + rand()%(attempt[employee_helped].size());
			int employee_helping = employee_helped;

			// We choose at random another employee who's gonna receive those animals
			while (employee_helping == employee_helped) {
				employee_helping = rand()%employees_in_zone;
			}

			int tmp = attempt[employee_helping].size();

			// Take away the animals from the employee helped
			for (int i = 0; i < number_of_animals_taken; i++) {
				// Chooose an animal at random from the employee helped
				vector<int>::iterator it = (attempt[employee_helped].begin() + rand()%(attempt[employee_helped].size()));
				// Add that animal to the employee helping
				attempt[employee_helping].push_back(*it);
				attempt_sum[employee_helping] += *it;
				attempt_sum[employee_helped] -= *it;
				// Remove that animal from the employee helped
				*it = attempt[employee_helped].back();
				attempt[employee_helped].pop_back();
			}

			// Chooose an animal at random from the animals of the employee helping that we didn't add
			vector<int>::iterator it = (attempt[employee_helping].begin() + rand()%(tmp));
			// Add the animal from the employee helping to the employee helped
			attempt[employee_helped].push_back(*it);
			attempt_sum[employee_helped] += *it;
			attempt_sum[employee_helping] -= *it;
			// Remove that animal from the employee helping
			*it = attempt[employee_helping].back();
			attempt[employee_helping].pop_back();

			simplified_variance_attempt = simplified_variance(attempt_sum);
			// If the metropolis criteria is satisfied, we update our current solution
			if (metropolis_criteria(simplified_variance_current_solution- simplified_variance_attempt, t)) {
				current_solution = attempt;
				current_solution_sum = attempt_sum;
				simplified_variance_current_solution = simplified_variance_attempt;

				// If our current solution is better, let's update our best solution
				if (simplified_variance_current_solution < simplified_variance_solution) {
					solution = current_solution;
					simplified_variance_solution = simplified_variance_current_solution;
					// Optimization : if the variance is null, we have the best possible solution
					if (simplified_variance_solution <= 0.0) {
						return 0.0;
					}
				}
			}

		}

		// Lowering the temperature
		t *= alpha;
	}

	return simplified_variance_solution;
}

double step_2_solver(int employees_in_zone, const vector<int>& zone, vector<vector<int>>& solution) {
	return simulated_annealing_solver(employees_in_zone, zone, solution, 1000, 10.0, 100, 0.9);
}