/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains brutefroce algorithm.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS
#include "SolveStrategy.hpp"
#include "../knapsack/InstanceProblem.hpp"
#include "../knapsack/InstanceSolution.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class implements bruteforce algorithm.
 *
 * @author Rostislav Novak
*/
class BruteForce : public SolveStrategy {
public:
	InstanceSolution solve(const InstanceProblem & problem) {
		auto things = problem.getThings();
		unsigned long combinations = (long)2 << (things.size() -1) ;
		unsigned long solveCombination = 0;
		int maxValue = 0, maxWeight = 0, tempWeight = 0, tempValue = 0;
		unsigned long tested = 0;

		for(unsigned long combination = 0; combination < combinations; ++combination) {
			auto weightAndValue = count_weight_and_value(things, combination);
			tempWeight = weightAndValue.second;
			tempValue = weightAndValue.first;
			tested++;
			if(tempWeight <= problem.getCapacity() && tempValue > maxValue) {
				solveCombination = combination;
				maxValue = tempValue;
				maxWeight = tempWeight;
			}
		}

		return InstanceSolution(solveCombination, maxValue, maxWeight, tested);
	}

	virtual std::string name() {
		return "BruteForce";
	}
};