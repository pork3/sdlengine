#ifndef GAME_OPTIONS_HPP_
#define GAME_OPTIONS_HPP_
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 
 	Last updated by: Chase Craig
 	Last updated on: Feb. 24, 2019
 
  	Purpose:
        This header file is to provide a configurations class for managing game options such as frame rate.
        	This inherits from OnlyOne, which enforces that there may only be 1 such instance of this object.
		
		This function differs from the Settings.hpp file by being created per window/per logic handler, while
			the classes in Settings.hpp are global settings.
	
	Usage:
		In both, the constructor is for setting the target rate of the object (if the system is under load,
			this target may be missed). Can get the target or set the target using the getters and setters.
 
 
 */
#include "../utils/Utils.hpp"
namespace Management{
    class WindowOptions{
    public:
        // Default constructor that sets the target frame rate to 60 frames per second
        WindowOptions() : frameRateTarget(60) {}

        // A constructor with a specified target frame rate
        WindowOptions(short targetRate) : frameRateTarget(targetRate) {}

        // Getter for the frame rate target
        short getFrameRateTarget(){return this->frameRateTarget;}

        // Setter for the frame rate target
        void setFrameRateTarget(short target){this->frameRateTarget = target;}

    protected:
        // The target frame rate for the window
        short frameRateTarget = 60;
    };

    class GameOptions{
    public:
        // Default constructor that sets the target tick (see latter) rate to 60 main logic loops (ticks)
        //       per second
        GameOptions() : tickRateTarget(60){}

        // A constructor with a specified target tick rate
        GameOptions(short targetRate) : tickRateTarget(targetRate){}

        // Getter for the tick rate target
        short getTickRateTarget(){return this->tickRateTarget;}

        // Setter for the tick rate target
        void setTickRateTarget(short tr){this->tickRateTarget = tr;}

    protected:
        // The target tick rate for the window
        short tickRateTarget = 60;

    };
}

#endif // GAME_OPTIONS_HPP_
