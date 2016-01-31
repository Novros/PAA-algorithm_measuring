/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
#include <iostream>
#include <string>
#include <ctime>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS
#include "algorithms/SolveStrategy.hpp"
#include "algorithms/Genetic.hpp"
#include "file/InputFromFile.hpp"
#include "file/OutputToFile.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
using namespace std;
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#define SOLUTION_VALUE 4068

void info(const std::string & str) {
	cout << "[INFO] " << str << std::endl;
}

void debug(const std::string & str) {
	cout << "[DEBUG] " << str << std::endl;
}

void run_algorithm(std::string filePath, SolveStrategy *algorithm) {
	rlib::file::InputFromFile file(filePath);
	rlib::file::OutputToFile output("output/out_" + algorithm->name() + ".csv");

	double averageTime;
	double averageMistake;
	unsigned long averageTested;

	int n = 0;

	while( !file.isEndOfFile() ) {
		std::string line = file.readLine();
		
		if(line.length() < 3) {
			break;
		}
		
		n++;
		auto problem = InstanceProblem(line);

		//cout << line << endl;
		
		clock_t begin_solution_time = clock();
		auto solution = algorithm->solve(problem);
		clock_t end_solution_time = clock();
		double elipsed_time = (double(end_solution_time - begin_solution_time) / CLOCKS_PER_SEC)*1000;
		averageTime = elipsed_time;
		averageMistake = (double(SOLUTION_VALUE - solution.getValue()) / SOLUTION_VALUE);

		//cout << algorithm->name() << " " << elipsed_time << " (" << solution.getValue() << ", " << solution.getWeight() << ")" << endl;
	}
	
	// Print out
	//cout << "Avarage time " + algorithm->name() + ": " << averageTime << endl;
	//cout << "Avarage mistake " + algorithm->name() + ": " << averageMistake << endl;

	// Save to file
	output << averageTime << "\t" << averageMistake << "\n";
}


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int main(int argc, char** argv) {
	//info("Program started!");

	std::string test_instnace = "instances/genetic.inst.dat";
	Genetic* algorithm = new Genetic();

	run_algorithm(test_instnace, algorithm);

	//info("Program ended.");
	return 0;
}
