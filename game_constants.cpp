/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "game_constants.h"

#include <game_constants_loader.h>
#include <engine_strings.h>
#include <engine_data.h>

using namespace std;

/// BEGIN SCRIPT-GENERATED CONSTANT INITIALIZATIONS
uint32_t Game_Constants::MAP_PADDING=0;
uint8_t Game_Constants::MAP_CHARACTER_ERROR=0;
string Game_Constants::MAP_CHARACTER_ERROR_COLOR="";
string Game_Constants::MAP_CHARACTER_ERROR_BACKGROUND_COLOR="";
bool Game_Constants::MAP_CHARACTER_ERROR_SOLID=false;
uint8_t Game_Constants::MAP_CHARACTER_PADDING=0;
string Game_Constants::MAP_CHARACTER_PADDING_COLOR="";
string Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR="";
bool Game_Constants::MAP_CHARACTER_PADDING_SOLID=false;
string Game_Constants::DISPLAY_FONT="";
int32_t Game_Constants::CREATURE_COLLISION_REDUCTION=0;
int32_t Game_Constants::CREATURE_COLLISION_STEPS=0;
string Game_Constants::INITIAL_MAP="";
/// END SCRIPT-GENERATED CONSTANT INITIALIZATIONS

void Game_Constants_Loader::set_game_constant (string name, string value) {
    if (name == "zoom_rate") {
        Engine_Data::ZOOM_RATE = Strings::string_to_double(value);
    } else if (name == "zoom_min") {
        Engine_Data::ZOOM_MIN = Strings::string_to_double(value);
    } else if (name == "zoom_max") {
        Engine_Data::ZOOM_MAX = Strings::string_to_double(value);
    }

    /// BEGIN SCRIPT-GENERATED CONSTANT SETUP
    else if(name=="map_padding"){
        Game_Constants::MAP_PADDING=Strings::string_to_unsigned_long(value);
    }
    else if(name=="map_character_error"){
        Game_Constants::MAP_CHARACTER_ERROR=Strings::string_to_unsigned_long(value);
    }
    else if(name=="map_character_error_color"){
        Game_Constants::MAP_CHARACTER_ERROR_COLOR=value;
    }
    else if(name=="map_character_error_background_color"){
        Game_Constants::MAP_CHARACTER_ERROR_BACKGROUND_COLOR=value;
    }
    else if(name=="map_character_error_solid"){
        Game_Constants::MAP_CHARACTER_ERROR_SOLID=Strings::string_to_bool(value);
    }
    else if(name=="map_character_padding"){
        Game_Constants::MAP_CHARACTER_PADDING=Strings::string_to_unsigned_long(value);
    }
    else if(name=="map_character_padding_color"){
        Game_Constants::MAP_CHARACTER_PADDING_COLOR=value;
    }
    else if(name=="map_character_padding_background_color"){
        Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR=value;
    }
    else if(name=="map_character_padding_solid"){
        Game_Constants::MAP_CHARACTER_PADDING_SOLID=Strings::string_to_bool(value);
    }
    else if(name=="display_font"){
        Game_Constants::DISPLAY_FONT=value;
    }
    else if(name=="creature_collision_reduction"){
        Game_Constants::CREATURE_COLLISION_REDUCTION=Strings::string_to_long(value);
    }
    else if(name=="creature_collision_steps"){
        Game_Constants::CREATURE_COLLISION_STEPS=Strings::string_to_long(value);
    }
    else if(name=="initial_map"){
        Game_Constants::INITIAL_MAP=value;
    }
    /// END SCRIPT-GENERATED CONSTANT SETUP
}
