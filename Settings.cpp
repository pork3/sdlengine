#include "./lib/json/json.h"
#include "Settings.hpp"


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
