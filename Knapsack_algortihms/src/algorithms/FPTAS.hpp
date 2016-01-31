/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains FPTAS algorihm.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS
#include "SolveStrategy.hpp"
#include "DynamicForward.hpp"
#include "../knapsack/InstanceProblem.hpp"
#include "../knapsack/InstanceSolution.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class implements FPTAS algorihm.
 *
 * @author Rostislav Novak
*/
class FPTAS : public SolveStrategy {
private:
	double epsilon = 0.2;

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	/*---------------------------------------------------------------------------------------------------------------*/
	InstanceSolution solve(const InstanceProblem & problem) {
		auto things = problem.getThings();

		int C_max = std::max_element(things.begin(), things.end(), pairCompare)[0].first;
		double K = (epsilon * C_max) / things.size();

		InstanceProblem fptas_problem(problem.getCapacity());
		fptas_problem.setId(problem.getId());
		for(auto it = things.begin(); it != things.end(); ++it) {
			fptas_problem.addThing(it->first/K, it->second);
		}

		DynamicForward forward;
		return forward.solve(fptas_problem);
	}

	virtual std::string name() {
		return "FPTAS";
	}
};