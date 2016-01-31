/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains instance problem for knapsack problem.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 */

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iterator>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class contains oen instance of knapsack problem.
 *
 * @author Rostislav Novak
*/
class InstanceProblem {
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Variables
private:
	/** Id of instance. */
	int id = 0;
	/** Maximal capacity of bag. */
	int capacity = 0;
	/** Things, which we can put into bag. Pair is (value, weight) */
	std::vector<std::pair<int, int>> things;

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
public:
	/** Empty constructor. */
	InstanceProblem() {}

	/** Simple constructor. Create problem without items. */
	InstanceProblem(const int & maxCapacity) : capacity(maxCapacity) {
	}

	/** Create instance problem from one line from file. */
	InstanceProblem(const std::string & line) {
		std::istringstream iss(line);
		
		std::vector<std::string> parsedLine;
		copy(std::istream_iterator<std::string>(iss),
			 std::istream_iterator<std::string>(),
			 back_inserter(parsedLine));

		auto it = parsedLine.begin();
		id = std::stoi(*it++);
		it++;
		capacity = std::stoi(*it++);
		for( ; it != parsedLine.end(); it += 2) {
			things.push_back(std::make_pair(std::stoi(*(it+1)), std::stoi(*it)));
		}
	}

	/** Copy constructor */
	InstanceProblem(const InstanceProblem & other) {
		this->id = other.id;
		this->capacity = other.capacity;
		this->things = other.things;
	}

	/*------------------------------------------- Setter methods ---------------------------------------------------*/
	/** Set id of instance. */
	void setId(const int & id) { this->id = id; }

	/*------------------------------------------- Getter methods ---------------------------------------------------*/
	/** Return id of instance. */
	int getId() const { return id; }
	/** Return maximal capacity of bag. */
	int getCapacity() const { return capacity; }
	/** Return vector of things for this instance. */
	std::vector<std::pair<int, int>> getThings() const { return things;	}

	/*------------------------------------------- Other methods ---------------------------------------------------*/
	/** Add thing into instance. */
	void addThing(const int & value, const int & weight) {
		things.push_back(std::make_pair(value, weight));
	}
	
};