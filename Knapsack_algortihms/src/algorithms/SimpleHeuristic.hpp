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

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS
#include "SolveStrategy.hpp"
#include "../knapsack/InstanceProblem.hpp"
#include "../knapsack/InstanceSolution.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class provides simple interface pro strategy pattern.
 *
 * @author Rostislav Novak
*/
class SimpleHeuristic : public SolveStrategy {
	
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	InstanceSolution solve(const InstanceProblem & problem) {
		auto things = problem.getThings();
		unsigned int size = things.size();
		std::vector<std::pair<int, double>> ratios;
		unsigned long tested = 0;

		for(unsigned int i = 0; i < size; ++i) {
			ratios.push_back(std::make_pair(i, things[i].first / things[i].second));
		}
		std::sort(ratios.begin(), ratios.end(), pairCompare);

		int maxValue = 0, maxWeight = 0, position = 0;
		unsigned long solveCombination = 0;
		for(auto it = ratios.begin(); it != ratios.end(); ++it) {
			position = it->first;
			tested++;
			if(maxWeight +  things[position].second > problem.getCapacity()) {
				break;
			}
			maxValue += things[position].first;
			maxWeight += things[position].second;
			solveCombination |= 1 << position;
		}

		return InstanceSolution(solveCombination, maxValue, maxWeight, tested);
	}

	virtual std::string name() {
		return "SimpleHeuristic";
	}
};