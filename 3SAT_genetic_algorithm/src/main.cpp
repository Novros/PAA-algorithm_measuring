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
#include "algorithms/SatSolveStrategy.hpp"
#include "algorithms/Genetic.hpp"
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

void run_algorithm(std::string file_path, SatSolveStrategy *algorithm) {
	int begin = file_path.find("sat_");
	std::string prefix = file_path.substr(begin, file_path.size() - begin - 4);
	std::string solution_path = "solutions/" + file_path.substr(begin, file_path.size() - begin - 8) + "sol.dat";
	cout << solution_path << endl;

	rlib::file::InputFromFile file(file_path);
	rlib::file::InputFromFile solution_file(solution_path);

	rlib::file::OutputToFile output("output/out_" + algorithm->name() + ".csv");

	double averageTime = 0.0;
	double averageMistake = 0.0;
	double maxMistake = 0.0;
	double relative_mistake = 0;
	double average_solutions = 0.0;

	int n = 0;
	std::string line = file.readLine();
	std::istringstream iss(line);
	std::vector<std::string> parsedLine;
	copy(std::istream_iterator<std::string>(iss),
		 std::istream_iterator<std::string>(),
		 back_inserter(parsedLine));
	int variables_count = std::stoi(parsedLine[2]);
	int clauses_count = std::stoi(parsedLine[3]);
	while( !file.isEndOfFile() ) {
		line = file.readLine();
		std::string solution_line = solution_file.readLine();

		if(line.length() < 3) {
			break;
		}
		
		int bf_solution = std::stoi(solution_line.substr(0, solution_line.find(" ")));
		auto problem = InstanceProblem(line, variables_count, clauses_count);
		// cout << line << endl;
		if( bf_solution != 0) {
			n++;
			clock_t begin_solution_time = clock();
			auto solution = algorithm->solve(problem);	
			clock_t end_solution_time = clock();
			double elipsed_time = (double(end_solution_time - begin_solution_time) / CLOCKS_PER_SEC)*1000;
			averageTime += elipsed_time;
			cout << bf_solution << " - " << solution.get_weight() << " / " << bf_solution << endl;
			relative_mistake = (std::abs(1.0*(bf_solution - solution.get_weight())) / bf_solution);
			average_solutions += solution.get_solutions();
			averageMistake += relative_mistake;
			if(relative_mistake > maxMistake) {
				maxMistake = relative_mistake;
			}

			cout << algorithm->name() << " " << elipsed_time << ", " << solution.get_weight() << ", " << relative_mistake << endl;
		}
	}

	averageTime = averageTime/n;
	averageMistake = averageMistake/n;
	average_solutions = average_solutions/n;
	
	// Print out
	cout << "Avarage time " + algorithm->name() + ": " << averageTime << endl;
	cout << "Avarage mistake " + algorithm->name() + ": " << averageMistake << endl;
	cout << "Max mistake " + algorithm->name() + ": " << maxMistake << endl;
	cout << "Avarage solutions " + algorithm->name() + ": " << average_solutions << endl;

	// Save to file
	output << prefix << "\t" << averageTime << "\t" << averageMistake << "\t" << maxMistake << "\t" << average_solutions << "\n";
}


/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
int main(int argc, char** argv) {
	info("Program started!");

	std::vector<std::string> problems_files;
	std::vector<std::string> dirFiles;
	getdir("instances/", dirFiles);
	for(auto it = dirFiles.begin(); it != dirFiles.end(); ++it) {
		if(*it != ".." && *it != ".") {
			problems_files.push_back("instances/" + *it);
		}
	}
	
	std::vector<SatSolveStrategy*> algorithms;
	algorithms.push_back(new Genetic());

	int i = 0;
	for(auto it = problems_files.begin(); it != problems_files.end(); ++it) {
		cout << "/////////////////////////////////////////////////////////////////////////////////////////" << endl;
		cout << *it << endl;

		for(auto algorithm = algorithms.begin(); algorithm != algorithms.end(); ++algorithm) {
			cout << "---------------------------------------------------------------------------------------" << endl;
			run_algorithm(*it, *algorithm);
		}

		cout << endl;
		i++;
	}

	info("Program ended.");
	return 0;
}
