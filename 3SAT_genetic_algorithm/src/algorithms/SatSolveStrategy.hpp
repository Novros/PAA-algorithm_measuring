/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains interface for strategy pattern.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <iterator>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS
#include "../sat/InstanceProblem.hpp"
#include "../sat/InstanceSolution.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class provides simple interface pro strategy pattern.
 *
 * @author Rostislav Novak
*/
class SatSolveStrategy {
public:
	/** Interface method for algorithms which solves knapsack problem. */
	virtual InstanceSolution solve(const InstanceProblem & problem) = 0;
	/** Return name of algortihm. */
	virtual std::string name() = 0;

protected:
	/*---------------------------------------------------------------------------------------------------------------*/
	int count_weight(std::vector<int> variables_weight, int combination) {
		int weight = 0;
		for (unsigned int i = 0; i < variables_weight.size(); ++i) {
			if(combination & 1) {
				weight += variables_weight[i];
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

	int count_clauses_met(const std::vector<std::vector<int>> & formula, const int & combination) {
		bool clause_value = false;
		int count = 0;
		for(auto it = formula.begin(); it != formula.end(); it++) {
			clause_value = false;	
			for(auto jt = (*(it)).begin(); jt != (*(it)).end(); jt++) {
				clause_value = clause_value | get_variable_value(*jt, combination);
				if(clause_value) {
					break;
				}
			}
			if(clause_value) {
				count++;
			}
		}
		return count;
	}
};