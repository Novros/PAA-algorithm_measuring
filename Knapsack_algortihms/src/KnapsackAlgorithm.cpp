#include "KnapsackAlgorithm.hpp"

InstanceSolution KnapsackAlgorithm::solveByBAndB(const InstanceProblem & problem) {
	BoundAndBranch algorithm;
	return algorithm.solve(problem);
}

InstanceSolution KnapsackAlgorithm::solveByDynamicForward(const InstanceProblem & problem) {
	DynamicBackward algorithm;
	return algorithm.solve(problem);
}

InstanceSolution KnapsackAlgorithm::solveByDynamicBackward(const InstanceProblem & problem) {
	DynamicForward algorithm;
	return algorithm.solve(problem);
}

InstanceSolution KnapsackAlgorithm::solveByFPTAS(const InstanceProblem & problem) {
	FPTAS algorithm;
	return algorithm.solve(problem);
}

InstanceSolution KnapsackAlgorithm::solveByForce(const InstanceProblem & problem) {
	BruteForce algorithm;
	return algorithm.solve(problem);
}

InstanceSolution KnapsackAlgorithm::solveByHeuristic(const InstanceProblem & problem) {
	SimpleHeuristic algorithm;
	return algorithm.solve(problem);
}

InstanceSolution KnapsackAlgorithm::solveByGeneticAlgorithm(const InstanceProblem & problem) {
	Genetic algorithm;
	return algorithm.solve(problem);
}