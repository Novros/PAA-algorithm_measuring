/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
#pragma once
/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
/**
 * @file This file contains class for writting to file.
 * @author  Rostislav Novak <rostislav.novak92@gmail.com>
 * @version 1.0
 *
 * @section LICENSE This program is free software; you can redistribute it and/or
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
 * This class provides writting to file.
 *
 * @author Rostislav Novak
*/
class OutputToFile {
	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Variables
private:
	/**
	 * Name of file.
	 */
	std::string fileName;
	/**
	 * Stream for writting to file.
	 */
	std::ofstream fileStream;

protected:

public:

	/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
	// Methods
private:

protected:

public:
	/*********************************************** Constructors ****************************************************/
	// TODO Check exceptions.
	// TODO Binary writting and so on.
	// TODO Add operators lile << and >>.
	// TODO Check stream states

	/**
	 * @brief Create output stream for file.
	 * 
	 * @param fileName Name of file, which will be created.
	 * @param append True for appending. Default value is false.
	 * @param binary True for writting binary. Default values is false.
	 */
	OutputToFile(const std::string & fileName, const bool append = false, const bool binary = false) {
		this->fileName = fileName;
		fileStream.open(fileName, std::ios_base::out|std::ios_base::app);
	}

	/**
	 * @brief Default desctructore which close stream.
	 */
	~OutputToFile() {
		fileStream.close();
	}

	OutputToFile(const OutputToFile & other) {
		fileStream.close();
		fileName = other.fileName;
		fileStream.open(fileName, std::ios_base::out|std::ios_base::app);
	}

	/************************************************* Getters *******************************************************/
	/**
	 * @brief It returns stream for writting.
	 * 
	 * @return Returns ostream stream, which is openned for writting.
	 */
	std::ostream & getStream() {
		return fileStream;
	}

	/************************************************** Others *******************************************************/
	/**
	 * @brief Write type T to file.
	 * 
	 * @param text Object which will be writed to file.
	 */
	template <class T>
	void write(const T & text) {
		fileStream << text;
	}

	/**
	 * @brief Write type T to file and plus line.
	 * 
	 * @param text Object which will be writed to file.
	 */
	template <class T>
	void writeLine(const T & text) {
		fileStream << text << std::endl;
	}

	/************************************************ Operators ******************************************************/
	/**
	 * @brief Overrided operator for simple typing.
	 * 
	 * @param text Object which will be writed to file.
	 */
	template <class T>
	std::ofstream & operator << (const T & text) {
		fileStream << text;
		return fileStream;
	}
	
};}}