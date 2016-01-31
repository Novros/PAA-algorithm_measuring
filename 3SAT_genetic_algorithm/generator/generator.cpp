#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iterator>
#include <ctime>
#include <cstdlib>
#include "OutputToFile.hpp"

const unsigned int random_number(const unsigned int & max) {
	return std::rand() % max + 1;
}

std::string generate_negation() {
	if (random_number(2) == 2) {
		return "-";
	} else {
		return "";
	}
}

std::string generate_instance(const int & clauses, const int & variables, const int & variables_in_clause, const int & max_weight) {
	std::string output = "";
	for(int i = 0; i < variables; i++) {
		output += std::to_string(random_number(max_weight)) + " ";
	} 
	output += "0 ";

	int previous_value = 0, value = 0;
	int num_variables_in_clause = 0;
	for(int i = 0; i < clauses; i++) {
		if(variables_in_clause == 0) {
			num_variables_in_clause = random_number(variables);
		} else {
			num_variables_in_clause = variables_in_clause;
		}
		for(int j = 0; j < num_variables_in_clause; j++) {
			value = random_number(variables);
			while( value == previous_value) {
				value = random_number(variables);
			}
			output += generate_negation() + std::to_string(value) + " ";
			previous_value = value;
		}
		output += "0 ";
	}

	return output;
}

int count_weight(int* variables, const int & num_variables, int combination) {
	int weight = 0;
	for (unsigned int i = 0; i < num_variables; ++i) {
		if(combination & 1) {
			weight += variables[i];
		}
		combination = combination >> 1;
	}
	return weight;
}

bool get_variable_value(int index, int combination) {
	bool negative = false;
	bool value = false;

	if (index < 0) {
		index = -index;
		negative = true;
	}
	index--;
	combination = combination >> index;
	value = combination & 1;

	return negative ? !value : value;
}

bool formula_value(const std::vector<std::vector<int>> & formula, const int & combination) {
	bool value = true;
	bool clause_value = false;
	for(auto it = formula.begin(); it != formula.end(); it++) {
		if(!value) {
			return false;
		}
		clause_value = false;	
		for(auto jt = (*(it)).begin(); jt != (*(it)).end(); jt++) {
			clause_value = clause_value | get_variable_value(*jt, combination);
			if(clause_value) {
				break;
			}
		}
		value = value & clause_value;
	}
	return value;
}

std::string combination_to_int(int combination, const int & n) {
	std::string output = "";

	for (unsigned int i = 0; i < n; ++i) {
		output += std::to_string(combination & 1);
		combination = combination >> 1;
	}

	return output;
}

std::string generate_solution(const int & variables, const int & clauses, std::string line) {
	std::string solution = "";

	std::istringstream iss(line);
	std::vector<std::string> parsedLine;
	copy(std::istream_iterator<std::string>(iss),
		 std::istream_iterator<std::string>(),
		 back_inserter(parsedLine));

	auto it = parsedLine.begin();
	int *variables_weight = new int[variables];
	std::vector<std::vector<int>> formula;
	
	for(int i = 0; i < variables; i++, it++) {
		variables_weight[i] = std::stoi(*(it));
	}
	it++;
	
	for(int i = 0; i < clauses; i++) {
		std::vector<int> clause;
		while(std::stoi(*(it)) != 0) {
			clause.push_back(std::stoi(*(it)));
			it++;
		}
		it++;
		formula.push_back(clause);
	}

	unsigned long combinations = (long)2 << (variables -1) ;
	unsigned long solveCombination = 0;
	int max_weight = 0;
	int solutions = 0;

	for(unsigned long combination = 0; combination < combinations; ++combination) {
		if(formula_value(formula, combination)) {
			solutions++;
			int weight = count_weight(variables_weight, variables, combination);
			if(weight > max_weight) {
				solveCombination = combination;
				max_weight = weight;
			}
		}
	}

	solution += std::to_string(max_weight) + " " + combination_to_int(solveCombination, variables) + " " + std::to_string(solutions) + " " + std::to_string(combinations) + " " + std::to_string((double)(1.0*solutions/combinations));

	delete [] variables_weight;
	return solution + "\n";
}

/*
Order of arguments: clauses, variables, variables in clause, instances
*/
int main(int argc, char** argv) {
	std::srand(std::time(0));

	if(argc < 6) {
		std::cout << "Missing arguments.\ngenerator [num_clauses] [num_variables] [variables_in_clause] [instances] [max_weight]\ncalled with:" << std::endl;
		for(int i = 0; i < argc; i++) {
			std::cout << argv[i] << std::endl;
		}
		return 1;
	}

	int clauses = std::atoi(argv[1]);
	int variables = std::atoi(argv[2]);
	int variables_in_clause = std::atoi(argv[3]);
	int instances = std::atoi(argv[4]);
	int max_weight = std::atoi(argv[5]);

	std::string filename = std::string("sat_c") + argv[1] + "_v" + argv[2] + "_vc" + argv[3] + ".inst.dat";
	rlib::file::OutputToFile output(filename);
	filename = std::string("sat_c") + argv[1] + "_v" + argv[2] + "_vc" + argv[3] + ".sol.dat";
	rlib::file::OutputToFile solution(filename);

	output << "p cnf " << argv[2] << " " << argv[1] << "\n";
	std::string instance = "";
	for(int i = 0; i < instances; i++) {
		instance = generate_instance(clauses, variables, variables_in_clause, max_weight) + "\n";
		output << instance;
		solution << generate_solution(variables, clauses, instance);
	}

	return 0;
}