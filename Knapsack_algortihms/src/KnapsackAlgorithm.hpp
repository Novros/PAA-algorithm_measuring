/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains class which resolves Knapsackproblem.
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
#include "knapsack/InstanceProblem.hpp"
#include "knapsack/InstanceSolution.hpp"
#include "algorithms/SolveStrategy.hpp"
#include "algorithms/BoundAndBranch.hpp"
#include "algorithms/Bruteforce.hpp"
#include "algorithms/DynamicForward.hpp"
#include "algorithms/DynamicBackward.hpp"
#include "algorithms/FPTAS.hpp"
#include "algorithms/Genetic.hpp"
#include "algorithms/SimpleHeuristic.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class provides knapsack solution.
 *
 * @author Rostislav Novak
*/
class KnapsackAlgorithm {
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	// Solve knapsack problem by brute force
	InstanceSolution solveByForce(const InstanceProblem & problem);
	// Solve knapsack problem by simple greedy heuristic, weigh/cost
	InstanceSolution solveByHeuristic(const InstanceProblem & problem);
	// Start solving knapasack problem by bound & branch solution.
	InstanceSolution solveByBAndB(const InstanceProblem & problem);
	// Solve knapsack problem by forward dynamic programming.
	InstanceSolution solveByDynamicForward(const InstanceProblem & problem);
	// Solve knapsack problem by backward dynamic programming.
	InstanceSolution solveByDynamicBackward(const InstanceProblem & problem);
	// Solve knapsack problem by FTPAS algorithm.
	InstanceSolution solveByFPTAS(const InstanceProblem & problem);
	// Solve Knapsack problem by genetic algorithm
	InstanceSolution solveByGeneticAlgorithm(const InstanceProblem & problem);
};