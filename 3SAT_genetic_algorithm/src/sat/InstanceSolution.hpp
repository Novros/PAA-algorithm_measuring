/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains solution for instance problem of knapsack problem.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
#include <string>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class contains solution for one instance.
 *
 * @author Rostislav Novak
*/
 class InstanceSolution {
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Variables
private:
	/** Id of instance. */
	int id = 0;
	/** Bit vector of solution. */
	const unsigned long solution = 0;
	/** Weight for solution. */
	const int weight = 0;

	int solutions = 0;

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	/** Simple constructor. */
	InstanceSolution(const unsigned long & solution, const int & weight, const int & solutions = 0) : solution(solution), weight(weight) { 
		this->solutions = solutions;
	}

	/** Copy constructor */
	InstanceSolution(const InstanceSolution &instance) : solution(instance.solution), weight(instance.weight)
	{ }

	/*------------------------------------------- Setter methods ---------------------------------------------------*/
	void set_id(const int & id) { this->id = id; }

	/*------------------------------------------- Getter methods ---------------------------------------------------*/
	int get_id() const { return id; }
	int get_weight() const { return weight; }
	unsigned long get_solution() const { return solution; }
	int get_solutions() const { return solutions; }
};