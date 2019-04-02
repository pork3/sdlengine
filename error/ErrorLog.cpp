#include "ErrorLog.hpp"
#include <chrono>
#include <ctime>
#include <fstream>


namespace {

    #define BUFFERSIZE 256
    std::string GetTime(){
        /*getting 'c style' for most compatibility*/
        time_t tod = time(0);
        struct tm sec;
        char buffer[BUFFERSIZE];
        /*https://en.cppreference.com/w/cpp/chrono/c/strftime*/
        std::strftime(buffer, sizeof(buffer), "%d/%m/%y - %X", &sec);
        return buffer;
    }

    /*(check to see if file exists, sets up read/write modes for error log*/
    bool FileExists(const std::string& fname){
        if( FILE* file = fopen(fname.c_str(), "r") ){
            fclose(file);
            return true;
        } else {
            return false;
        }
    }




}

void ErrorLog::WriteError(std::string message) {

    std::ofstream file;
    std::string tod = GetTime();
    if( FileExists("Error.log") ){

        file.open("Error.log", std::ios_base::app);
        file << tod << std::endl << message << std::endl << std::endl;
        file.close();
    } else {
        file.open("Error.log");
        file << tod << std::endl << message << std::endl << std::endl;
    }

}
