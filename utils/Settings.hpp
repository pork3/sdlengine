// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
/*
 *	Last updated by: Zachary Bower
 *	Last updated on: Feb. 23, 2019
 *
 *	Purpose:
 *		This class contains all settings for creating defaults and allowing the user to change/access defaults
 *		This lass will make use of a JSON config, or some way of storing settings
 *
 *	Functions without comments are assumed to be a single line, set or get a single variable, and the
 *		comment is to be found next to the respective variable definition.
 */
#ifndef ENGINE_SETTINGS_H
#define ENGINE_SETTINGS_H
#include <string>

namespace Settings {


    /*settings for window creation*/
    namespace Window{
        int window_width;
        int window_height;
        bool is_fullscreen;
        bool is_center;
        void SetWidth();
        void SetHeight();

    }

    namespace Shader{

        std::string default_dir;
        // what is default_dir?

    }

    namespace Sound{

        int volume;

    }

    namespace Multimedia{

        std::string texture_dir;
        std::string model_dir;
        std::string music_dir;
    }

    namespace Logging{
        std::string error_dir;
        /* boolean for indicating if time is logged*/
        bool is_time;

    }

    namespace Debug{
        bool display_fps;
        bool console_write;

    }
};


#endif //ENGINE_SETTINGS_H
