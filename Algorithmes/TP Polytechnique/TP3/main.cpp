#include <boost/program_options.hpp> 
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
#include <string>

#include "solver.h"

using namespace boost::program_options;
using namespace std;

int main(int argc, char* argv[])
{
	bool print_solution = false;
    bool print_time = false;
    bool verbose = false;
    double expected_output = 0.0;
    double precision = 0.0;
    double max_duration = 3*60;
	string file_name;
	ifstream input_file;
    variables_map vm;

	// Declare the supported options
	options_description desc("Allowed options");
	desc.add_options()
	    ("help,h", "produce help message")
	    ("file,f", value<string>(), "(mandatory) sets input file name")
	    ("print,p", "prints the solution")
        ("verbose,v", "describes the search to the user")
        ("expected_output,e", value<double>(), "specifies the expected output")
        ("time,t", "prints the elapsed time at each iteration of the search")
        ("duration,d", value<double>(),"max duration (in seconds) of the search (3 minutes by default)")
	;

	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help")) {
	    cout << desc << "\n";
	    return 1;
	}

	if (vm.count("file")) {
	    file_name = vm["file"].as<string>();
	} else {
	    cout << "Please specify input file with the -f or --file option (use -h or --help to display the allowed options).\n";
	    return 1;
	}

	if (vm.count("print")) {
	    print_solution = true;
	}

    if (vm.count("time")) {
        print_time = true;
    }

    if (vm.count("verbose")) {
        verbose = true;
    }

    if (vm.count("expected_output")) {
        expected_output = vm["expected_output"].as<double>();
        string tmp = to_string(expected_output);
        int dot = tmp.size() - 1, n = 0;
        while (tmp[dot] == '0' && dot > 0) {
            n++;
            dot--;
        }
        while (tmp[dot] != '.' && dot > 0) {
            dot--;
        }

        n = tmp.size() - (dot + n + 1);
        if (dot == 0) n = 0;
        precision = 5*pow(10, -n-1);
    }

    if (vm.count("duration")) {
        max_duration = vm["duration"].as<double>();
    }

	// Init
	srand((unsigned)time(0));
    input_file.open(file_name);

    if(input_file.is_open()) {
        clock_t start;
        int employees, zoo_size;
        vector<vector<int>> zoo;
        vector<int> employees_partition;
        vector<double> variance_of_zone;
        vector<vector<vector<int>>> solution;
        double duration;
        double total_duration = 0.0;
        double best_solution_value = numeric_limits<double>::max();
        double solution_value;
        int iteration = 1;

        // Getting input
        input_file >> zoo_size >> employees;
        for (int i = 0; i < zoo_size; i++) {
            int zoo_set_size;
            input_file >> zoo_set_size;
            zoo.push_back(vector<int>(zoo_set_size));
            for (int j = 0; j < zoo_set_size; j++) {
                input_file >> zoo[i][j];
            }
        }

        if (verbose) {
            cout << "Input is as follows : " << endl;
            cout << zoo_size << " zones, " << employees << " employees" << endl;
            for (int i = 0; i < zoo_size; i++) {
                cout << "Zone " << i+1 << " : " << zoo[i].size() << " animals ";
                for (int j = 0; j < zoo[i].size(); j++) {
                    cout << " " << zoo[i][j];
                }
                cout << endl;
            }
            cout << endl << endl;
        }

        /*****************************************
         *      - PUTTING IT ALL TOGETHER -      *
         *             ACTUAL SOLVER             *
         *****************************************/

        // Init
        for (int i = 0; i < zoo_size; i++) {
            solution.push_back(vector<vector<int>>());
            variance_of_zone.push_back(numeric_limits<double>::max());
        }

        if (verbose) {
            cout << "Step 1 : getting a good partition of the employees using a greedy solver" << endl;
        }
        
        step_1_solver(employees, zoo, employees_partition);

        if (verbose) {
            cout << "Result :";
            for (int employees_in_zone : employees_partition) {
                cout << " " << employees_in_zone;
            }
            cout << endl << endl;
        }

        if (verbose) {
            cout << "Step 2 : assigning animals to employees with several simulated annealings" << endl;
        }

        do {
            // Solving and computing the duration
            // srand((unsigned)time(0));
            double step_2_end_time;
            vector<int> sum;

            if (verbose) {
                cout << "Iteration " << iteration << endl;
            }

            start = clock();
            step_2_end_time = start;

            for (int i = 0; i < zoo_size; i++) {
                double variance_current;
                double step_2_duration;
                vector<vector<int>> employees_assignement(employees_partition[i]);

                variance_current = step_2_solver(employees_partition[i], zoo[i], employees_assignement)/employees_partition[i];
                step_2_duration = (clock() - step_2_end_time)/((double)CLOCKS_PER_SEC);
                step_2_end_time = clock();

                if (variance_current < variance_of_zone[i]) {
                    variance_of_zone[i] = variance_current;
                    solution[i] = employees_assignement;
                }
            }

            for (int i = 0; i < zoo_size; i++) {
                for (int j = 0; j < solution[i].size(); j++) {
                    int sum_animal = 0;
                    for (int k = 0; k < solution[i][j].size(); k++) {
                        sum_animal += solution[i][j][k];
                    }
                    sum.push_back(sum_animal);
                }
            }

            solution_value = sqrt(simplified_variance(sum)/employees);

            duration = (clock() - start)/((double)CLOCKS_PER_SEC);

            if (solution_value < best_solution_value) {
                if (verbose) {
                    cout << "Better solution found !" << endl;
                    cout << "The standard deviation is : ";
                }

                // Updating best solution
                best_solution_value = solution_value;

                // Printing output
                cout << solution_value << endl;

                if (print_solution) {
                    if (verbose) {
                        cout << "The solution is : " << endl;
                    }
                    for (int i = 0; i < solution.size(); i++) {
                        if (verbose) {
                            cout << "Zone " << i+1 << " : ";
                        }
                        cout << solution[i].size();
                        if (verbose) {
                            cout << " employees";
                        }
                        cout << endl;
                        for (int j = 0; j < solution[i].size(); j++) {
                            if (verbose) {
                                cout << "Employee " << j+1 << " : ";
                            }
                            cout << solution[i][j].size() << " ";
                            if (verbose) {
                                cout << "animals ";
                            }
                            for (int k = 0; k < solution[i][j].size(); k++) {
                                cout << solution[i][j][k] << ((k < solution[i][j].size() - 1)? (" ") : (""));
                            }
                            cout << endl;
                        }
                    }
                }

                if (print_time) {
                    cout << "Elapsed time : " << total_duration + duration << " seconds" << endl;
                }
            } 
            else if (verbose) {
                cout << "No better solution found" << endl;
            }

            // Udpating duration and iteration
            total_duration += duration;
            iteration++;

            if(verbose) {
                cout << (total_duration/max_duration)*100 << "\% of time consumed" << endl;
                cout << endl;
            }
        } while (total_duration < max_duration && best_solution_value - expected_output > precision);

        if (verbose) {
            cout << "End of the search" << endl << endl;
        }

        if (vm.count("expected_output")) {
            double quality = (best_solution_value - expected_output > precision) ? (100*(1 - (best_solution_value - expected_output)/expected_output)) : (100);
            cout << "Our solution's standard deviation is : " << best_solution_value << endl;
            cout << "The expected standard deviation was : " << expected_output << endl;
            cout << "The quality of our solution is about " << quality << "\%" << endl;
            if (print_time) {
                cout << "Time to compute the final solution : " << total_duration << " seconds" << endl;
            }
        }


        // Cleaning up
        input_file.close();
    }

	return 0;
}