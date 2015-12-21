README - Florentin BURGEAT (1809123), Elliot SISTERON (1807165)

Installation on OSX/Linux :

	To compile :
		compile them all:
		make all 

		or:
		make vorace
		make dynamique
		make recuitSimule

	To execute :
		Execute vorace, dynamique or recuitSimule in the current folder with at least the -f parameter

	To clean object files :
		make clean

	To clean completely (binary + object files) :
		make mr-proper

Usage :

	Execute the file vorace, dynamique or recuitSimule.

	Use -f to read the input file.
	Use -p to print the result (i.e. displaying the content of each box).

	The output will be printed as follows : 
	n : <n>
	v : <volumes of items seperated by a space> 
	m : <m>
	c : <c>
	If -p is enabled, the full solution will be displayed as follows, for each box :
	box <box_number> (volume used <volume>), items inside :  <volume of items seperated by a space>
	solution : <solution>
	found in <duration>
	<name_of_solver, file_name, n, m, c, solution, duration> (this is a recap line)

	Warning : Depending on the size of the input file, the solver may take a (very) long time to compute the answer.

NB :
	
	The boost library is required to compile (used to hash vector<int> and for program_options).
	Please put the right link to your library in the makefile (INCLUDES and LIBS) in order to be able to compile.