
#ifndef Game_Manager_HPP_
#define Game_Manager_HPP_

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890

/*
 *
 *	Last updated by: Zachary Bower
 *	Last updated on: Mar 6, 2019
 *
 *	Purpose:
 *		This header class is to provide base classes for managing the game, added support for initializing
 *      libraries used, and access to n number of windows
 *
 *
 *
 */

// Includes other files
#include "../events/Listeners.hpp"
#include "../rendering/Window.hpp"
#include "../events/EventDispatcher.hpp"
// Different c libraries needed
#include <mutex> // For creation of "lockable"/"only-one-user-at-a-time" objects.
#include <thread> // For creation of threads (sub-programs running independently to each other but same code.
#include <string>
#include <unordered_set>
#include "../utils/GameOptions.hpp"
namespace Events{
    class EventDispatcher;
}
namespace Engine{

    class GameManager : public Management::OnlyOne{
    friend class Events::EventDispatcher;

    public:
        friend void jumperThread(GameManager* gm); // Serves as a jump point to run.
        // This function is to ensure that there is ONLY ONE instance of this object. This grabs the instance
        // 		and returns a reference to the object's pointer.
        static GameManager* &instance(void){static GameManager* game = new GameManager; return game;}

        // A function to request the starting of the game. The game can start paused if the argument is true.
        void StartGame(bool startPaused);

        // A function to request stopping of the game. A stopping event will be dispatched, however it is
        // 		cancellable based on if this was not forced.
        void StopGame(bool forced);

        // A function to pause the execution of tick events for the game.
        void PauseGame(void);

        // A function to resume the execution of tick events for the game.
        void ResumeGame(void);

        // A function to handle aborting the game (critical error), a reason to be logged should be supplied.
        void Abort(std::string reason);

        // A function meant to occupy a main thread for final cleanup. This will HALT THE THREAD UNTIL
        // 		the game thread has finished (joined our other threads).
        void WaitForGameEnd(void){
            mainGameThread->join();
        };

        /*function to initialized all OS specific libraries*/
        void InitSystems();

        /*wrapper function to initialized window*/
        Window* CreateWindow(std::string title, int height, int width);

        Management::GameOptions* GetOptions();

        static std::mutex* io_mutex;
    protected:
        std::thread* mainGameThread;

        void Run(); // A function that is called internally for running the game. Note: this function should be only called from a thread.
        bool gamePaused = false; // A bool stating whether the game is paused or not.
        GameManager() : startingTime(std::chrono::high_resolution_clock::now()), lastTick(std::chrono::high_resolution_clock::now()){}; // Default constructor. Protected so that this class can not be created multiple times, therefore enforcing a "create once" policy.
        ~GameManager(); // Default deconstructor.

        GameManager(const GameManager &gm){}

        bool gameRunning = false;
    private:
        bool gameSetup = false;
        std::chrono::high_resolution_clock::time_point startingTime;

        high_resolution_clock::time_point lastTick;
        Management::GameOptions* options;

        std::unordered_set<Window*> windows;

        //Window* window;
    };
    void jumperThread(GameManager* gm);
}



#endif //Game_Manager_HPP_
