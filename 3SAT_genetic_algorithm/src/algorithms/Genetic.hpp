/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains genetic algorithm.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
 #include <iostream>
 #include <ctime>
 #include <cstdlib>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS
#include "SatSolveStrategy.hpp"
#include "../sat/InstanceProblem.hpp"
#include "../sat/InstanceSolution.hpp"

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class implements genetic algorithm.
 *
 * @author Rostislav Novak
*/
class Genetic : public SatSolveStrategy {
private:
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Genetic algorithm setting.
	const unsigned int MAX_GENERATIONS = 100;	// Number of generations.
	const unsigned int CHROMOZOME_POPULATION = 150;	// How many chromozmes in population will be.
	const unsigned int TOURNAMENT_SIZE = CHROMOZOME_POPULATION/3;	// Tournament size in seleciton.
	const unsigned int ELITISM_SIZE = (int)(ceil(CHROMOZOME_POPULATION * 0.6));	// How many new population will be in new generation.
	const unsigned int CROSSOVER_CHANCE = 95;	// Probability of crossover. In %.
	const unsigned int MUTATION_CHANCE = 70;	// Probability of mutation. In %.
	const double MAX_CLAUSES_MET = 0.9;	// Ratio of met clauses againts number clauses in formula.
	const unsigned int PENALTY = 0;

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Simple structure of chromozome.
	struct Chromozome {
		unsigned int fitness = 0;
		unsigned long items = 0;
		Chromozome() {}
		Chromozome(const unsigned long i) { this->items = i; }
	};

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Simple structure of elites.
	struct Elite {
		Chromozome first;
		Chromozome second;

		Elite() {}

		Elite(const Chromozome & first, const Chromozome & second) {
			this->first = first;
			this->second = second;
		}
	};

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Supporting variables
	/** Number of items. */
	int n = 0;
	/** Max random item. */
	unsigned long rand_max_n = 1;
	/** Generation of population. */
	unsigned int generation = 0;
	/** Best fitness of generation. */
	unsigned int best_fitness = 0;
	/** Best fitness combination. */
	unsigned long best_combination = 0;
	/** Avarage fitness of generation. */
	unsigned int avarage_fitness = 0;
	/** Instance of proble, to get info about it.*/
	InstanceProblem problem;
	/** Actual population. */
	std::vector<Chromozome> population;
	/** New population, which will replace actual population. */
	std::vector<Chromozome> new_population;

	/*-------------------------------------------------------------------------------------------------------------------*/
public:
	InstanceSolution solve(const InstanceProblem & problem) {
		// Random number by time.
		std::srand(std::time(0));
		// Save instance problem for access from algorithm.
		this->problem = problem;
		// Set number of items.
		this->n = problem.get_variables_count();
		// Maximum of random for items.
		rand_max_n = (unsigned long)(1 << this->n);
		// Structure for elites.
		Elite elite;
		// Initialize population by random nubmers.
		initialize_population();
		// Get first information
		process_information();
		// Run algorithm.
		for(generation = 0; generation < MAX_GENERATIONS; generation++) {
			// Sort population by fitness.
			sort_population();
			// Tournament selection
			for(int i = 0; i < CHROMOZOME_POPULATION; i += 2) {
				// Elitism, only process the discarded chromosomes.
				if( i < (CHROMOZOME_POPULATION - ELITISM_SIZE)) {
					// Just add elite to new population.
					new_population.push_back(Chromozome(population[i].items));
					new_population.push_back(Chromozome(population[i+1].items));
				} else {
					// Select two elite chromozomes by tournament selection.
					elite = selection();
					// Crossover elite
					crossover(elite);
					// Mutate elite
					mutation(elite);
					// Andd new chromozmes to new population.
					new_population.push_back(elite.first);
					new_population.push_back(elite.second);
				}
			}
			// Process information about generation.
			process_information();
			// Print information out.
			// output();
			// Replace old generation by new generation.
			replace_generation();
		}

		int count = 0;
		for(auto it = population.begin(); it != population.end(); it++) {
			if(formula_value(problem.get_formula(), (*it).items)) {
				count++;
			}
		}

		return InstanceSolution(best_combination, best_fitness, count);
	}

	virtual std::string name() {
		return "Genetic";
	}

private:
	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Return random number in size of N. */
	const unsigned int random_number_by_n() const {
		return std::rand() % rand_max_n;
	}

	/** Return random number in size of N. */
	const unsigned int random_number(const unsigned int & max) const {
		return std::rand() % max;
	}

	/** Toss coin with propability chance. */
	const bool coin(const unsigned int chance) const {
		return std::rand() % 100 > chance;
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Initialize popuplation. */
	void initialize_population() {
		// Randomly generation first population.
		for (int i = 0; i < CHROMOZOME_POPULATION; ++i) {
			population.push_back(random_number_by_n());
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Compare two chromozomes by fitness. */
	static bool compare_fitness(const Chromozome & chromozome_1, const Chromozome & chromozome_2) {
		return chromozome_1.fitness > chromozome_2.fitness;
	}

	/** Sort population by fitness. */
	void sort_population() {
		std::sort(population.begin(), population.end(), compare_fitness);
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Crossover elite */
	void crossover(Elite & elite) {
		if(coin(CROSSOVER_CHANCE)) {
			// Choose crossover strategy
			//chromozome_crossover_one_point(elite.first.items, elite.second.items);
			//chromozome_crossover_two_point(elite.first.items, elite.second.items);
			chromozome_uniform(elite.first.items, elite.second.items);
		}
	}

	/** One point crossover. */
	void chromozome_crossover_one_point(unsigned long & chromozome_1, unsigned long & chromozome_2) {
		const unsigned long index = random_number_by_n();
		const unsigned long bit_vector = (0 - 1) << index;
		chromozome_bit_vector_change(chromozome_2, chromozome_1, bit_vector);
	}

	/** Two point crossover. */
	void chromozome_crossover_two_point(unsigned long & chromozome_1, unsigned long & chromozome_2) {
		const unsigned long index = random_number_by_n();
		const unsigned long index2 = random_number_by_n();
		unsigned long bit_vector = 0;

		if( index2 > index ) {
			bit_vector = ((0 - 1) << index2) + (~((0 - 1) << index));
		} else if (index2 == index) {
			bit_vector = (0 - 1) << index;
		} else {
			bit_vector = ((0 - 1) << index) + (~((0 - 1) << index2));
		}

		chromozome_bit_vector_change(chromozome_1, chromozome_2, bit_vector);
	}

	/** Uniform crossover. */
	void chromozome_uniform(unsigned long & chromozome_1, unsigned long & chromozome_2) {
		const unsigned long bit_vector = random_number_by_n();
		chromozome_bit_vector_change(chromozome_1, chromozome_2, bit_vector);
	}

	/** Support change by bit vector. */
	void chromozome_bit_vector_change(unsigned long & chromozome_1, unsigned long & chromozome_2, const unsigned long & bit_vector) {
		const unsigned long bit_vector_inversion = (~bit_vector);
		const unsigned long chromozome_1_temp = (chromozome_1 & bit_vector) + (bit_vector_inversion & chromozome_2);
		chromozome_2 = (chromozome_2 & bit_vector) + (bit_vector_inversion & chromozome_1);
		chromozome_1 = chromozome_1_temp;
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Mutate chromozomes. */
	void mutation(Elite & elite) {
		if(coin(MUTATION_CHANCE)) {
			chromozome_inversion(elite.first.items);
		}
		if(coin(MUTATION_CHANCE)) {
			chromozome_inversion(elite.second.items);
		}
	}

	/** Mutation by inversion. */
	void chromozome_inversion(unsigned long & chromozome) {
		const unsigned long index = 3;
		const unsigned int chance = (100.0 / this->n) * index;
		if (coin(chance)) {
			const unsigned long bit_vector = ((0 - 1) << index) + (~((0 - 1) << (index-1)));
			if ((chromozome >> (index-1)) & 1) {
				chromozome = chromozome & bit_vector;
			} else {
				chromozome = chromozome | (~bit_vector);
			}
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Select elite by tournament seleciton. */
	Elite selection() {
		return Elite(tournament_selection(), tournament_selection());
	}

	/** Tournament slection. */
	Chromozome tournament_selection() {
		unsigned int best = random_number(CHROMOZOME_POPULATION);
		unsigned int candidate;
		for (int i = 0; i < TOURNAMENT_SIZE; i++) {
			candidate = random_number(CHROMOZOME_POPULATION);
			if (population[candidate].fitness > population[best].fitness) {
				best = candidate;
			}
		}
		Chromozome chromozome;
		chromozome.items = population[best].items;
		return chromozome;
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Print some info about generation. */
	void output() {
		std::cout << generation << "\t" << best_fitness << "\t" << avarage_fitness << std::endl;
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Count fitness of chromozome and stores into it. */
	void fitness(Chromozome & chromozome) {
		int fitness = 0;
		int weight = count_weight(problem.get_variables_weight(), chromozome.items);
		int clauses_met = count_clauses_met(problem.get_formula(), chromozome.items);
		if (clauses_met < MAX_CLAUSES_MET*problem.get_clauses_count()) {
			// Penalty
			fitness = 0;
		} else {
			fitness = weight;
		}
		chromozome.fitness = fitness;
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	/** Get information from generation. */
	void process_information() {
		best_fitness = 0;
		avarage_fitness = 0;
		for( auto it = population.begin(); it != population.end(); it++) {
			fitness(*it);
			avarage_fitness += (*it).fitness;
			if( (*it).fitness > best_fitness ) {
				best_fitness = (*it).fitness;
				best_combination = (*it).items;
			}
		}
		avarage_fitness = avarage_fitness / CHROMOZOME_POPULATION;
	}

	/** Replace old generation with new generation. */
	void replace_generation() {
		population = new_population;
		new_population.clear();
	}
};
