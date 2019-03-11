#include "Error.hpp"
#include <chrono>
#include <ctime>
#include <fstream>

/*anonymous namespace for private 'helper functions'*/
namespace {
    /*Helper function to get the current time for the error log*/
#define BUFFERSIZE 126
    std::string GetTime(){
        /*getting 'c style' for most compatibility*/
        time_t tod = time(0);
        struct tm sec;
        char buffer[BUFFERSIZE];
        /*https://en.cppreference.com/w/cpp/chrono/c/strftime*/
        std::strftime(buffer, sizeof(buffer), "%d/%m/%y - %X", &sec);
        return buffer;
    };
}

void Error::WriteError(std::string message){
    std::ofstream log;
    log.open("error.log", std::fstream::app);
    /*log the time of day */
    std::string tod = GetTime();
    log << std::endl << tod << std::endl << message << std::endl << std::endl;
    log.close();
}

/*error.log format
 *
 * dd/mm/yyy - HH:MM
 * Error Message
 *
 *
 * */
