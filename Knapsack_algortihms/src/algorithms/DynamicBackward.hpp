/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains backward dynamic algortihm.
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
 * This class implements dynamic backward algorithm.
 *
 * @author Rostislav Novak
*/
class DynamicBackward : public SolveStrategy {
private:
	/*------------------------------------------- Dynamic helper ------------------------------------------------------*/
	class DynamicHelper {
	private:
		int **table;
		const int max_value;
		const int n;
		int infinity;

	public:
		DynamicHelper(const int & n, const int & max_value) : n(n), max_value(max_value) {
			infinity = 99999;
			table = new int*[n];
			for(int i = 0; i < n; i++) {
				table[i] = new int[max_value];
				for(int j = 0; j < max_value; j++) {
					table[i][j] = -1;
				}
			}
			
			for(int j = 0; j < max_value; j++) {
				table[0][j] = infinity;
			}
			table[0][0] = 0;
		}

		~DynamicHelper() {
			for(int i = 0; i < n; i++) {
				delete[] table[i];
			}
			delete[] table;
		}

		void put(const int & n, const int & value, int x) {
			table[n][value] = x;
		}

		int get(const int & n, const int & value) {
			if(value < 0)
				return infinity;
			return table[n][value];
		}

		void print() {
			for(int i = 0; i < n; i++) {
				for(int j = 0; j < max_value; j++) {
					std::cout << " " << table[i][j];
				}
				std::cout << std::endl;
			}
		}
	};

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	/*---------------------------------------------------------------------------------------------------------------*/
	InstanceSolution solve(const InstanceProblem & problem) {
		auto things = problem.getThings();
		int n = things.size() + 1, max_value = rest_count_value(things, 0) + 1, tempValue = 0;
		DynamicHelper table(n, max_value);
		unsigned long tested = 0;

		int value = 0, weight = 0;
		for(int i = max_value-1; i >= 0; i--) {
			weight = recursive_helper(n-1, i, things, table, tested);
			if(weight <= problem.getCapacity()) {
				value = i;
				break;
			}
		}

		return InstanceSolution(0, value, weight, tested);
	}

	virtual std::string name() {
		return "DynamicBackward";
	}

private:
	/*---------------------------------------------------------------------------------------------------------------*/
	int recursive_helper(const int & n, const int & value, const std::vector<std::pair<int, int>> & things, DynamicHelper & table, unsigned long & tested) {
		tested++;
		if( table.get(n,value) < 0 ) {
			int tempValue = std::min(
				recursive_helper(n-1, value, things, table, tested),
				recursive_helper(n-1, value - things[n-1].first, things, table, tested) + things[n-1].second);
			table.put(n, value, tempValue);
			return tempValue;
		}

		return table.get(n, value);
	}
};