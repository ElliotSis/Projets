README - Florentin BURGEAT (1809123), Jeremy CUGMAS (1814477), Elliot SISTERON (1807165)

Installation on OSX/Linux :

	To compile :
		make

		or:
		make all

		or:
		make TP3

	To execute :
		Execute TP3 in the current folder with at least the -f parameter

	To clean object files :
		make clean

	To clean completely (binary + object files) :
		make mr-proper

Usage :

	Execute the file TP3.

	Use -f or --file <input_file_path> to read the input file (mandatory).
	Use -p or --print to print the result (i.e. displaying the content of each box).
	Use -t or --time to print the time taken to compute the elapsed time.
	Use -v or --verbose to describe the search to the user.
	Use -e or --expected_output <expected_output_of_the_program> to specify an expected output.
	Use -h or --help to print the usage of the program.
	Use -d or -—duration <max_duration> to change the maximum duration (in seconds) of the search (3 minutes by default).

	Every time a better solution is found, the output will be printed as follows : 
	<standard deviation>
	If -p is enabled, the full solution will be displayed as follows :
	<number of employees in first set>
	<number of animals for the first employee in that set> <value of first animal of employee> _ <value of last animal of employee>
	…
	<number of animals for the last employee in that set> <value of first animal of employee> _ <value of last animal of employee>
	…
	<number of employees in last set>
	<number of animals for the first employee in that set> <value of first animal of employee> _ <value of last animal of employee>
	If -t is enabled, the time taken to compute the result will be displayed :
	Found in <duration_to_find_this_solution>

	Warning : Depending on the size of the input file, the solver may take a (very) long time to compute an answer.
	The search will last at most <max_duration> minutes.

NB :
	
	The boost library is required to compile (for program_options).
	Please put the right link to your library in the makefile (INCLUDES and LIBS) in order to be able to compile.