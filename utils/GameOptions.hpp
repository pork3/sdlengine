#ifndef GAME_OPTIONS_HPP_
#define GAME_OPTIONS_HPP_
// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Chase Craig
 *	Last updated on: Feb. 24, 2019
 *
 *	Purpose:
 *      This header file is to provide a configurations class for managing game options such as frame rate.
 *      This inherits from OnlyOne, which enforces that there may only be 1 such instance of this object.
 *
 *
 */
#include "../utils/utils.hpp"
namespace Management{
    class GameOptions : public OnlyOne{
    public:
        /*
            Getter's and Setter's for protected variables below.
        */
        static GameOptions* &instance(){static GameOptions* opts= new GameOptions; return opts;}

        void setFrameRateTarget(short fr){this->frameRateTarget = fr;}
        short getFrameRateTarget(){return this->frameRateTarget;}
        short getTickRateTarget(){return this->tickRateTarget;}
        void setTickRateTarget(short tr){this->tickRateTarget = tr;}


        // Extend functionality to allow for arbitrary options to be set/get.

    protected:
        short frameRateTarget = 60;
        short tickRateTarget = 60;
        GameOptions(){}
    };
}

#endif // GAME_OPTIONS_HPP_
