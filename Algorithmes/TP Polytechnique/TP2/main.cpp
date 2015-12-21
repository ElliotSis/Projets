#include <boost/program_options.hpp> 
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>

#include "solvers.h"

using namespace boost::program_options;
using namespace std;

int main(int argc, char* argv[])
{
	bool print_solution = false;
	string file_name;
	ifstream input_file;
	int solver_used;

	// Declare the supported options
	options_description desc("Allowed options");
	desc.add_options()
	    ("help,h", "produce help message")
	    ("file_name,f", value<string>(), "(mandatory) sets input file name")
	    ("print_solution,p", "prints the solution")
	;

	variables_map vm;
	store(parse_command_line(argc, argv, desc), vm);
	notify(vm);

	if (vm.count("help")) {
	    cout << desc << "\n";
	    return 1;
	}

	if (vm.count("file_name")) {
	    file_name = vm["file_name"].as<string>();
	} else {
	    cout << "Please specify input file.\n";
	    return 1;
	}

	if (vm.count("print_solution")) {
	    print_solution = true;
	}

	// Init
	solver_used = get_solver_used();
	srand((unsigned)time(0));
    input_file.open(file_name);

    if(input_file.is_open()) {
        clock_t start;
        double duration;
        int n, m, c;
        int* v;
        int solution;

        // Getting input
        input_file >> n >> m >> c;

        // Allocating v
        v = new int[n];

        // Printing status
        cout << "Running the " << solvers_names[solver_used] << " on the file " << file_name << endl;

        // Printing input
        cout << "n : " << n << endl;
        cout << "v : ";

        // Filling the array
        for (int i = 0; i < n; i++) {
            input_file >> v[i];
            // Printing input
            cout << v[i] << " ";
        }
        cout << endl;

        // Printing input
        cout << "m : " << m  << endl; 
        cout << "c : " << c << endl;

        // Solving and computing the duration
        start = clock();
        solution = (*(solvers[solver_used]))(v, n, c, m, print_solution);
        duration = (clock() - start)/((double)CLOCKS_PER_SEC);

        // Printing output
        if (solution >= 0) {
        	cout << "solution : " << solution << endl;
	        cout << "found in " << duration << " seconds" << endl;
	        cout << solvers_names[solver_used] << ", " << file_name << ", " << n << ", "; 
	        cout << m << ", " << c << ", "  << solution  << ", " << duration << endl << endl;
        }
        

        // Cleaning up
        delete[] v;
        input_file.close();
    }

	return 0;
}