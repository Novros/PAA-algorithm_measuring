/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains bound and branch algorithm
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
 * This class implements bound and branch algorithm.
 *
 * @author Rostislav Novak
*/
class BoundAndBranch : public SolveStrategy {
private:
	/*------------------------------------------- Solve helper ------------------------------------------------------*/
	struct SolveHelper {
		int value = 0;
		int weight = 0;
		unsigned long combination = 0;
		unsigned long tested = 0;
	};
	
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	InstanceSolution solve(const InstanceProblem & problem) {
		auto things = problem.getThings();
		SolveHelper solution;

		recursive_helper(things, 0, 0, solution, things.size(), problem.getCapacity());
		
		return InstanceSolution(solution.combination, solution.value, solution.weight, solution.tested);
	}

	virtual std::string name() {
		return "BoundAndBranch";
	}

private:
	/*---------------------------------------------------------------------------------------------------------------*/
	void recursive_helper(const std::vector<std::pair<int, int>> & things,
										   const int & depth, const unsigned long & combination,
										   SolveHelper & solution,
										   const int & max_depth, const int & max_capacity) {
		auto weightAndValue = count_weight_and_value(things, combination);
		int if_value = weightAndValue.first + rest_count_value(things, depth);
		solution.tested = solution.tested + 1;

		// Check if i am in max depth or i exceed capacity of knapsack or i can not find better value.
		if(depth > max_depth || weightAndValue.second > max_capacity || if_value < solution.value) {
			return;
		}
		
		// weightAndValue.first = value, weightAndValue.second = weight
		if(weightAndValue.second <= max_capacity && weightAndValue.first > solution.value) {
			solution.combination = combination;
			solution.value = weightAndValue.first;
			solution.weight = weightAndValue.second;
		}

		// Call other combinations.
		recursive_helper(things, depth+1, b_and_b_combination(combination, depth, 0), solution, max_depth, max_capacity);
		recursive_helper(things, depth+1, b_and_b_combination(combination, depth, 1), solution, max_depth, max_capacity);
	}

	/*---------------------------------------------------------------------------------------------------------------*/
	unsigned long b_and_b_combination(const unsigned long & combination, const int & depth, const int & value) {
		unsigned long setBit = (long) value << depth;
		return combination + setBit;
	}
};