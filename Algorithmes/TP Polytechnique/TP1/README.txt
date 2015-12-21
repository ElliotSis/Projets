README - Florentin BURGEAT (1809123), Elliot SISTERON (1807165)

Installation on OSX/Linux :

	To compile :
		make

	To execute :
		Execute TP1 in the bin/ folder

	To clean object files :
		make clean

	To clean completely (binary + object files) :
		make mr-proper

Usage :

	Execute the TP1 file.
	
	The program will read of the files located in the input directory.
	It will use this input to generate arrays of integers, and then sort them and compute the time it took to do that.

	An output.csv file will be generated in the executable directory.
	Every line of the output file will be as follows : 
	[name of the sort], [name of the input file], [size of the array], [seconds it took to sort it]

	Warning : Depending on the number of files used as input and the size of those files, the sorting time may be long (especially for the bubble sorts…).

NB :
	
	The strnatcmp function made by Martin Pool was used to read the input files by natural order.