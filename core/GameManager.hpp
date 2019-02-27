#ifndef Game_Manager_HPP_
#define Game_Manager_HPP_

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Chase Craig
 *	Last updated on: Feb. 19, 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for managing the game.
 *
 *
 *
 *
 */


// Includes other files
#include "../events/Listeners.hpp"
#include <vector>
#include <unordered_set>

namespace Engine{
    class GameManager{
        static GameManager* &instance(){static GameManager* game = new GameManager; return game;}


    };

}



#endif //Game_Manager_HPP_
