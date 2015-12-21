#include <algorithm>
#include <cstdio>
#include <ctime>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "strnatcmp.h"
#include "sorts.h"

using namespace std;

const string HELP_TEXT = "Usage :\n\tExecute the TP1 file.\n\n\tThe program will read the txt files located in the input directory.\n\tIt will use this input to generate and sort arrays of integer.\n\tThe time required to execute those operations will then be computed.\n\n\tAn output.csv file will be generated in the executable directory.\n\tEvery line of the output file will be as follows :\n\t[name of the sort], [name of the input file], [size of the array], [seconds it took to sort it]\n";
const string OUTPUT_NAME = "output.csv";
const string INPUT_PATH = "./input/"; 

vector<string> input_files(){
    DIR* pdir;
    dirent* entry = nullptr;
    vector<string> files;

    // opening the directory and looking up all of the .txt files names
    pdir = opendir(INPUT_PATH.c_str());

    while((entry = readdir(pdir))) {
        string file_name = entry->d_name;
        if(file_name.find(".txt") != string::npos) {
            files.push_back(file_name);
        }
    }

    // sorting the files by natural order
    sort(files.begin(), files.end(), [] (const string& a, const string& b) -> bool {return (strnatcmp(a.c_str(), b.c_str()) < 0);});

    return files;
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        cout << HELP_TEXT << endl;
    }
    else {
        ofstream output;

        // initiating random seed
        srand((unsigned)time(0));

        output.open(OUTPUT_NAME);

        if(output.is_open()) {
            // for each sort
            for(int i = 0; i < NUMBER_OF_SORTS; i++) {
                // for each input file
                for(string file_name : input_files()) {
                    ifstream input_file;
                    input_file.open(INPUT_PATH + file_name);

                    if(input_file.is_open()) {
                        clock_t start;
                        double duration;
                        string line;
                        ifstream tmp;
                        int number_of_lines; 
                        int* tab;

                        // getting the size of the array and allocating it
                        tmp.open(INPUT_PATH + file_name);
                        number_of_lines = count(istreambuf_iterator<char>(tmp), istreambuf_iterator<char>(), '\n'); 
                        tab = new int[number_of_lines];

                        // printing status
                        cout << "Running the sort " << sort_functions_names[i] << " on the file " << file_name << endl;
                        cout << "\t Size of the array : " << number_of_lines << endl;

                        // filling the array
                        for (int j = 0; j < number_of_lines; j++) {
                            getline(input_file, line);
                            tab[j] = atoi(line.c_str());
                            // cout << tab[j] << " ";
                        }
                        // cout << endl;

                        // sorting the array, computing the time it took
                        start = clock();
                        (*(sort_functions[i]))(tab, number_of_lines);
                        duration = (clock() - start)/((double)CLOCKS_PER_SEC);

                        // for (int j = 0; j < number_of_lines; j++) {
                        //    cout << tab[j] << " ";
                        // }
                        // cout << endl;

                        // writing in the output file
                        output << sort_functions_names[i] << ", " << file_name << ", " << number_of_lines << ", " << duration << endl; 
                        
                        // printing status
                        cout << "\t Computation time : " << duration << endl;

                        // freeing memory
                        delete[] tab;
                        input_file.close();
                    }
                }
            }

            output.close();
        }
    }
    return 0;
}
