/*
 *	Last updated by: Linshu Huang
 *	Last updated on: March. 11, 2019
 *
 *	Purpose:
 *		This class contains all settings for creating defaults and allowing the user to change/access defaults
 *		This lass will make use of a JSON config, or some way of storing settings
 *
 *	Functions without comments are assumed to be a single line, set or get a single variable, and the
 *		comment is to be found next to the respective variable definition.
 */
/*
#include </home/linshu/programs/VTK-6.3.0/ThirdParty/jsoncpp/vtkjsoncpp/json/json.h>
#include "Settings.hpp"
#include <fstream>

// credit: https://stackoverflow.com/questions/32205981/reading-json-files-in-c



std::ifstream config_file("../config.json", std::ifstream::binary);
config_file >> config;
cout<<config;

if (!config["Window"].isNull()) {
    if (!config["Window"]["window_width"].isNull()) {
        void Window::SetWidth {
            window_width = config["Window"]["window_width"];
        }
    }
}
Settings setting;
cout<<setting.window_width<<endl;

/*
// json is something like this:
"Window": {
        "window_width": 800,
        "window_height":800,
        "is_fullscreen":false,
        "is_center":true },
    
    "Shader": {
        "default_dir":"res/shaders"
    },

    "Sound":{
        "volume":40
    },

    "Multimedia" : {
        "texture_dir":"res/textures",
        "model_dir":"res/obj",
        "music_dir":"res/"
    },

    "Logging" : {
        "error_dir":"err/",
        "is_time":true
    },

    "Debug":{
        "display_fps":true,
        "console_write":true
    }
*/

/*


void GetVal(Json::Value &config, int* setting){

    if( config.isNull() )
        return;
    *setting = config.asInt();
}

void GetVal(Json::Value &config, bool* setting)
{
    if (config.isNull())
        return;

    *setting = config.asBool();
}

void GetVal(Json::Value &config, float* setting)
{
    if (config.isNull())
        return;

    *setting = config.asFloat();
}
*/