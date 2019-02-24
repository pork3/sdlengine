#ifndef ENGINE_ERROR_H
#define ENGINE_ERROR_H
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *	Last updated by: Zachary Bower
 *	Last updated on: Feb. 23, 2019
 *
 *	Purpose:
 *		This class contains all access to error logging. This will be used by the entire system
 *		to write an error log file to display any errors that may occur. The default method is to append
 *		to the file. The file will be saved in /err/ directory and will named error.log
 *		The format of the error file will be a standard text file
 *
 *	Functions without comments are assumed to be a single line, set or get a single variable, and the
 *		comment is to be found next to the respective variable definition.
 */

#include <string>

namespace Error {

    void WriteError(std::string message);

}


#endif //ENGINE_ERROR_H
