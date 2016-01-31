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
	/** Value for solution. */
	const int value = 0;
	/** Weight for solution. */
	const int weight = 0;
	/** */
	const int n = 0;
	/** How many states were tested. */
	const unsigned long tested = 0;

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	/** Simple constructor. */
	InstanceSolution(const unsigned long & solution, const int & value, const int & weight, const unsigned long & tested = 0)
	: solution(solution), value(value), weight(weight), tested(tested)
	{ }

	/** Copy constructor */
	InstanceSolution(const InstanceSolution &instance) : solution(instance.solution), value(instance.value), weight(instance.weight), tested(instance.tested) {
	}

	/*------------------------------------------- Setter methods ---------------------------------------------------*/
	void setId(const int & id) { this->id = id; }

	/*------------------------------------------- Getter methods ---------------------------------------------------*/
	int getId() const { return id; }
	int getValue() const { return value; }
	int getWeight() const { return weight; }
	unsigned long getSolution() const { return solution; }
	unsigned long getTested() const { return tested; }
};