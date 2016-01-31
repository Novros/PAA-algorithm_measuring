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
#include "algorithms/Bruteforce.hpp"
#include "algorithms/BoundAndBranch.hpp"
#include "algorithms/DynamicForward.hpp"
#include "algorithms/FPTAS.hpp"
#include "algorithms/SimpleHeuristic.hpp"
#include "file/InputFromFile.hpp"
#include "file/OutputToFile.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
using namespace std;
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

void info(const std::string & str) {
	cout << "[INFO] " << str << std::endl;
}

void debug(const std::string & str) {
	cout << "[DEBUG] " << str << std::endl;
}

int getdir (string dir, vector<string> &files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

void run_algorithm(std::string filePath, SolveStrategy *algorithm) {
	int begin = filePath.find("knap_");
	std::string prefix = filePath.substr(begin, filePath.size() - begin - 4);
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

		cout << line << endl;
		
		clock_t begin_solution_time = clock();
		auto solution = algorithm->solve(problem);
		clock_t end_solution_time = clock();
		double elipsed_time = (double(end_solution_time - begin_solution_time) / CLOCKS_PER_SEC)*1000;
		averageTime += elipsed_time;
		averageTested += solution.getTested();

		cout << algorithm->name() << " " << elipsed_time << " (" << solution.getValue() << ", " << solution.getWeight() << ")" << endl;
	}

	averageTime = averageTime/n;
	averageMistake = averageMistake/n;
	averageTested = averageTested/n;
	
	// Print out
	cout << "Avarage time " + algorithm->name() + ": " << averageTime << endl;
	cout << "Avarage mistake " + algorithm->name() + ": " << averageMistake << endl;
	cout << "Avarage tested " + algorithm->name() + ": " << averageTested << endl;

	// Save to file
	output << prefix << "\t" << averageTime << "\t" << averageMistake << "\t" << averageTested << "\n";
}


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int main(int argc, char** argv) {
	info("Program started!");

	std::vector<std::string> problemsFiles;

	std::vector<std::string> dirFiles;
	getdir("instances/", dirFiles);
	for(auto it = dirFiles.begin(); it != dirFiles.end(); ++it) {
		if(*it != ".." && *it != ".") {
			problemsFiles.push_back("instances/" + *it);
		}
	}
	
	std::vector<SolveStrategy*> algorithms;
	algorithms.push_back(new SimpleHeuristic());
    algorithms.push_back(new BoundAndBranch());
    algorithms.push_back(new BruteForce());
    algorithms.push_back(new DynamicForward());
    algorithms.push_back(new FPTAS());

	for(auto it = problemsFiles.begin(); it != problemsFiles.end(); ++it) {
		cout << "/////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << *it << endl;

		for(auto algorithm = algorithms.begin(); algorithm != algorithms.end(); ++algorithm) {
			cout << "---------------------------------------------------------------------------------------" << endl;
			run_algorithm(*it, *algorithm);
		}

		cout << endl;
	}

	info("Program ended.");
	return 0;
}
