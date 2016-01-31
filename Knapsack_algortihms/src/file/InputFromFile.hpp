/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains definition of class for input from file.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 *
 * @section LICENSE* This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
**/

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// STL HEADERS
#include <iostream>
#include <fstream>
#include <string>

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
// OWN HEADERS

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
namespace rlib { namespace file {
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * This class represents simple input from file.
 *
 * @author Rostislav Novak
*/
class InputFromFile {
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Variables
private:
	/**
	 * Input stream for reading from file.
	 */
	std::ifstream inputStream;

protected:

public:

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
private:

protected:

public:
	/*********************************************** Constructors ****************************************************/
	/**
	 * @brief Create input from file and open file.
	 * 
	 * @param fileName Name of file name, which will be read.
	 */
	InputFromFile(const std::string & fileName) {
		inputStream.open(fileName);
	}

	/**
	 * @brief Default destructor, which will close file.
	 */
	~InputFromFile() {
		inputStream.close();
	}

	/************************************************** Others *******************************************************/
	// TODO Add operators lile << and >>.
	
	/**
	 * @brief Reads one line from file.
	 * @details It will reads, until stream is open.
	 * 
	 * @return Returns one line from file in string.
	 */
	const std::string readLine() {
		std::string line;
		if (inputStream.is_open()) {
			getline (inputStream, line);
		}
		return line;
	}

	/**
	 * @brief Read whole file.
	 * 
	 * @return Returns whole file in string.
	 */
	const std::string readFile() {
		std::string file = "";
		std::string line;
		if (inputStream.is_open()) {
			while ( getline (inputStream, line) ) {
				file += line + "\n";
		  	}
		}
		return file;
	}

	bool isEndOfFile() const {
		return !inputStream.is_open();
	}

};}}