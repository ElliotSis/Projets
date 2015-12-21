#include "solvers.h"

#include <algorithm>
#include <boost/functional/hash.hpp>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <unordered_map>
#include <vector>

using namespace std;

// Computes the volume of a single box
int volume(const vector<int>& box) {
	int res = 0;
	for (int value : box) {
		res += value;
	}
	return res;
}

// Prints the solution
void print_boxes(const vector<vector<int>>& solution) {
	int i = 1;
	for (const vector<int>& box : solution) {
		cout << "box " << i++ << " (volume used " << volume(box) << "), items inside : ";
		for (int item : box) {
			cout << item << " ";
		}
		cout << endl;
	}
}

/************************ 
 *   GREEDY ALGORITHM   *
 ************************/


int greedy_solver(int* v, int n, int c, int m, bool print_solution) {
	int v_sorted[n];
	multiset<int> capacities;
	int solution = 0;
	// To reconstruct the solution
	vector<vector<int>> reconstructed_solution(m);

	// Copying the array (we're going to need to sort it)
	for (int i = 0; i < n; i++) {
		v_sorted[i] = v[i];
	}

	// Sorting the array by decreasing order
	sort(v_sorted, v_sorted + n, greater<int>());

	// Initializing a set of capacities
	// We use a set for optimization, as it is an ordered container
	// It is a multiset, as values can be equal
	for (int i = 0; i < m; i++) {
		capacities.insert(c);
	}

	for (int i = 0; i < n; i++) {
		for (multiset<int>::iterator it = capacities.begin(); it != capacities.end(); it++) {
			int min_capacity = *it;
			int min_capacity_filled = min_capacity - v_sorted[i];

			// If we can put the item in the box with the minimum volume left, we do
			if (min_capacity_filled >= 0) {
				capacities.erase(it);

				// We only keep the boxes that still have some space left
				if(min_capacity_filled > 0) {
					capacities.insert(min_capacity_filled);
				}

				solution += v_sorted[i];

				// We update the reconstructed solution if necessary
				// We add the item to the box with the same volume left inside
				if (print_solution) {
					for (int j = 0; j < m; j++) {
						if (c - volume(reconstructed_solution[j]) == min_capacity) {
							reconstructed_solution[j].push_back(v_sorted[i]);
							break;
						}
					}
				}

				break;
			} 
		}
	}

	// Printing the reconstructed solution
	if (print_solution) {
		print_boxes(reconstructed_solution);
	}

	return solution;
}


/************************* 
 *  DYNAMIC PROGRAMMING  *
 *************************/


// Hash function of a vector using boost
template < typename SEQUENCE > struct seq_hash
{
    std::size_t operator() ( const SEQUENCE& seq ) const
    {
        std::size_t hash = 0 ;
        boost::hash_range( hash, seq.begin(), seq.end() ) ;
        return hash ;
    }
};

template < typename SEQUENCE, typename T >
using seq_map = std::unordered_map< SEQUENCE, T, seq_hash<SEQUENCE> >;

// Computes the number of combinations using Pascal's triangle rule and dynamic programming
int number_of_combinations(int n, int k) {
	int c[n+1][k+1];

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= min(i, k); j++) {
			if ((j==0) || (j==i)) {
				c[i][j] = 1;
			}
			else {
				c[i][j] = c[i-1][j-1] + c[i-1][j]; 
			}
		}
	}

	return c[n][k];
}

// Generates the weak compositions
void generate_weak_compositions(int c, int m, vector<vector<int>>& weak_compositions, vector<int> composition = vector<int>()) {
    if (c > 0) {
        for(int i = 0; i <= m; i++) {
        	composition.push_back(m - i);
        	generate_weak_compositions(c-1, i, weak_compositions, composition);
        	composition.pop_back();
        }
    } 
    else {
        composition.push_back(m);
       	weak_compositions.push_back(composition);
    }
}

int dynamic_programming_solver(int* v, int n, int c, int m, bool print_solution) {
	vector<int> end_composition(c+1);
	vector<vector<int>> weak_compositions;
	// unordered_map for optimization purposes
	vector<seq_map<vector<int>, int>> dynamic_table(n);
	// To reconstruct the solution
	vector<vector<int>> reconstructed_solution(n);

	if (n * number_of_combinations(m + c, c) > 2000000) {
		cout << "Too big to be solved with dynamic programming" << endl;
		return -1;
	}

	// Compute all of the weak compositions
	generate_weak_compositions(c, m, weak_compositions);

	// Initialization
	// For the first item
	// For each weak composition
	for (vector<int>& composition : weak_compositions) {
		dynamic_table[0][composition] = 0;

		// If we can put the item in a box, let's put it there
		for (int k = v[0]; k <= c; k++) {
			if (composition[k] > 0) {
				dynamic_table[0][composition] = v[0];
				break;
			}
		}
	}

	// Dynamic table construction
	// For each item
	for (int i = 1; i < n; i++) {
		// For each weak composition
		for (vector<int>& composition : weak_compositions) {
			// Apply the induction : selection of the best solution between putting the item somewhere or leaving it
			// For now, the best solution is to leave it
			int best_possibility = dynamic_table[i-1][composition];

			// Check if it's better to put the item in a box
			for (int k = v[i]; k <= c; k++) {
				vector<int> changed_composition(composition);

				if (changed_composition[k] > 0) {
					int possibility;

					changed_composition[k] -= 1;
					changed_composition[k-v[i]] += 1;
					possibility = v[i] + dynamic_table[i-1][changed_composition];

					if (possibility > best_possibility) {
						best_possibility = possibility;
					}
				}
			}

			dynamic_table[i][composition] = best_possibility;
		}
	}

	// The weak composition that will give us the solution
	for (int k = 0; k < c; k++) {
		end_composition[k] = 0;
	}
	end_composition[c] = m;

	// Printing the reconstructed solution
	if (print_solution) {
		print_boxes(reconstructed_solution);
	}

	return dynamic_table[n-1][end_composition];
}


/************************* 
 *  SIMULATED ANNEALING  *
 *************************/


bool metropolis_criteria(int delta, double theta) {
	return (delta >= 0 || exp(delta/theta) >= (rand() / (double)(RAND_MAX)));
}

int simulated_annealing_solver(int* v, int n, int c, int m, bool print_solution, int k_max, double t, int p, double alpha) {
	vector<vector<int>> best_solution(m), current_solution(m);
	vector<int> remaining_items(n);
	int total_volume = m * c;
	int best_solution_volume = 0, current_solution_volume = 0;

	// Remaining items initialization
	for (int i = 0; i < n; i++) {
		remaining_items[i] = v[i];
	}

	for (int k = 0; k < k_max; k++) {
		for (int j = 0; j < p; j++) {
			vector<vector<int>> attempt(current_solution);
			vector<int> items_deleted;
			int attempt_volume = current_solution_volume;
			// Generating a new attempt
			// We choose a box at random
			// We choose an item amongst the remaining ones at random, to add it to the box
			int box = rand()%(m);
			vector<int>::iterator it = (remaining_items.begin() + rand()%(remaining_items.size()));
			int item_added = *(it);
			
			// While we can't put the item inside the box, we keep removing one of the box's items at random
			while (c - volume(attempt[box]) < item_added) {
				vector<int>::iterator itt = (attempt[box].begin() + rand()%(attempt[box].size()));
				int item_deleted = *(itt);
				attempt[box].erase(itt);
				items_deleted.push_back(item_deleted);
				attempt_volume -= item_deleted;
			}

			// We put that item inside the box
			attempt[box].push_back(item_added);
			attempt_volume += item_added;

			// If the metropolis criteria is satisfied, we update our current solution
			if (metropolis_criteria(attempt_volume - current_solution_volume, t)) {
				current_solution = attempt;
				current_solution_volume = attempt_volume;

				// Removing the item that we used for the attempt
				remaining_items.erase(it);

				// If we deleted items in a box, we add them to the remaining items
				for (int item : items_deleted) {
					remaining_items.push_back(item);
				}

				// If our current solution is better, let's update our best solution
				if (current_solution_volume > best_solution_volume) {
					best_solution = current_solution;
					best_solution_volume = current_solution_volume;
					// Optimization : if all items are put in the boxes or all the boxes are filled, we have the best possible solution
					if (remaining_items.size() <= 0 || best_solution_volume >= total_volume) {
						goto stop;
					}
				}
			}

		}

		// Lowering the temperature
		t *= alpha;
	}

	// Printing the solution
	stop:
	if (print_solution) {
		print_boxes(best_solution);
	}

	return best_solution_volume;
}

int simulated_annealing_solver(int* v, int n, int c, int m, bool print_solution){
	return simulated_annealing_solver(v, n, c, m, print_solution, 1000, 10.0, 100, 0.9);
}