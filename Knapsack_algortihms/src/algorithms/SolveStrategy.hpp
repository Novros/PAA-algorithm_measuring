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
#include "../knapsack/InstanceProblem.hpp"
#include "../knapsack/InstanceSolution.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class provides simple interface pro strategy pattern.
 *
 * @author Rostislav Novak
*/
class SolveStrategy {
public:
	/** Interface method for algorithms which solves knapsack problem. */
	virtual InstanceSolution solve(const InstanceProblem & problem) = 0;
	/** Return name of algortihm. */
	virtual std::string name() = 0;

protected:
	/*---------------------------------------------------------------------------------------------------------------*/
	std::pair<int, int> count_weight_and_value(const std::vector<std::pair<int,int>> & things, unsigned long combination ) {
		int weight = 0, value = 0;

		for (unsigned int i = 0; i < things.size(); ++i) {
			if(combination & 1) {
				weight += things[i].second;
				value += things[i].first;
			}
			combination = combination >> 1;
		}

		return std::make_pair(value, weight);
	}

	/*---------------------------------------------------------------------------------------------------------------*/
	int rest_count_value(const std::vector<std::pair<int,int>> & things, const int & n) {
		int value = 0;
		for (unsigned int i = n; i < things.size(); ++i) {
			value += things[i].first;
		}
		return value;
	}
};

static bool pairCompare(const std::pair<double, int> & first, const std::pair<double, int> & second) {
	return first.first < second.first;
}