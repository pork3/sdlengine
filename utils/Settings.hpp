#ifndef ENGINE_SETTINGS_H
#define ENGINE_SETTINGS_H

// All comments shall be less than 110 characters, as displayed from the line below.
// 45678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
/*
 *	Last updated by: Chase Craig
 *	Last updated on: Mar. 11, 2019
 *
 *	Purpose:
 *		This class contains all settings for creating defaults and allowing the user to change/access defaults
 *		This lass will make use of a JSON config, or some way of storing settings
 *
 *	Functions without comments are assumed to be a single line, set or get a single variable, and the
 *		comment is to be found next to the respective variable definition.
 */
#include <string>

namespace Settings {


    // Settings for window properties
    namespace Window{

        int window_width;
        int window_height;
        bool is_fullscreen;
        bool is_center;
    }
	
	// Settings for default shader directory
    namespace Shader{

        std::string default_dir;

    }
	// Settings for the exponential amplitude multiplier (volume) for sound played to a sound board.
    namespace Sound{

        int volume;

    }

	// Settings for the default texture, model and music directory for multimedia assets.
    namespace Multimedia{

        std::string texture_dir;
        std::string model_dir;
        std::string music_dir;
    }

	// Setting for the default logging directory and logging time.
    namespace Logging{
        std::string error_dir;
        /* boolean for indicating if time is logged*/
        bool is_time;

    }
	
	// Settings for what information is logged when running, when debugging.
    namespace Debug{
        bool display_fps;
        bool console_write;

    }

};


#endif //ENGINE_SETTINGS_H
