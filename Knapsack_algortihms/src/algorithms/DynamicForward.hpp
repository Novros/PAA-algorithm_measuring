/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains forward dynamic algortihm.
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
 * This class implements dynamic forward algorithm.
 *
 * @author Rostislav Novak
*/
class DynamicForward : public SolveStrategy {
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

		for(int i = 0; i < max_value; i++) {
			for( int j = 1; j < n; j++) {
				tempValue = std::min(table.get(j-1,i), (table.get(j-1, i-things[j-1].first) + things[j-1].second));
				table.put(j, i, tempValue);
				tested++;
			}
		}

		int value = 0, weight = 0;
		for(int i = max_value-1; i >= 0; i--) {
			if(table.get(n-1,i) <= problem.getCapacity()) {
				weight = table.get(n-1,i);
				value = i;
				break;
			}
		}

		return InstanceSolution(0, value, weight, tested);
	}

	virtual std::string name() {
		return "DynamicForward";
	}
};