/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains instance problem for knapsack problem.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iterator>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class contains one instance of sat problem.
 *
 * @author Rostislav Novak
*/
class InstanceProblem {
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Variables
private:
	/** Id of instance. */
	int id = 0;
	/** Count of variables. */
	int variables_count = 0;
	/** Count of clauses in formula. */
	int clauses_count = 0;
	/** Weight of varaibles. */
	std::vector<int> variables_weight;
	/** Formula of sat problem. */
	std::vector<std::vector<int>> formula;

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	/** Empty constructor. */
	InstanceProblem() {}

	/** Simple constructor. Create problem without items. */
	InstanceProblem(const int & variables_count, const int & clauses_count) : variables_count(variables_count),  clauses_count(clauses_count) {
	}

	/** Create instance problem from one line from file. */
	InstanceProblem(const std::string & line, const int & variables_count, const int & clauses_count) {
		this->variables_count = variables_count;
		this->clauses_count = clauses_count;
		std::istringstream iss(line);
		std::vector<std::string> parsedLine;
		copy(std::istream_iterator<std::string>(iss),
			 std::istream_iterator<std::string>(),
			 back_inserter(parsedLine));

		auto it = parsedLine.begin();
		for(int i = 0; i < variables_count; i++, it++) {
			variables_weight.push_back(std::stoi(*(it)));
		}
		it++;
		
		for(int i = 0; i < clauses_count; i++) {
			std::vector<int> clause;
			while(std::stoi(*(it)) != 0) {
				clause.push_back(std::stoi(*(it)));
				it++;
			}
			it++;
			formula.push_back(clause);
		}
	}

	/** Copy constructor */
	InstanceProblem(const InstanceProblem & other) : variables_count(other.variables_count), clauses_count(other.clauses_count){
		this->id = other.id;
		this->formula = other.formula;
		this->variables_weight = other.variables_weight;
	}

	/*------------------------------------------- Setter methods ---------------------------------------------------*/
	/** Set id of instance. */
	void setId(const int & id) { this->id = id; }

	/*------------------------------------------- Getter methods ---------------------------------------------------*/
	/** Return id of instance. */
	int getId() const { return id; }
	/** Return count of variables. */
	int get_variables_count() const { return variables_count; }
	/** Return count of clauses in formula.*/
	int get_clauses_count() const { return clauses_count; }
	/** Return formula*/
	std::vector<std::vector<int>> get_formula() const { return formula;	}
	/** Return weight of variables. */
	std::vector<int> get_variables_weight() const { return variables_weight; }

	InstanceProblem & operator =(const InstanceProblem & other) {
		if (this == &other) {
			return *this;
		}
		this->id = other.id;
		this->variables_count = other.variables_count;
		this->clauses_count = other.clauses_count;
		this->formula = other.formula;
		this->variables_weight = other.variables_weight;
		return *this;
	}
};
