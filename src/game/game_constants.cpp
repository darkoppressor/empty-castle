/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "game_constants.h"

#include <game/game_constants_loader.h>
#include <strings/engine_strings.h>
#include <data/engine_data.h>

using namespace std;

// BEGIN SCRIPT-GENERATED CONSTANT INITIALIZATIONS
int32_t Game_Constants::MAP_PADDING = 0;
uint8_t Game_Constants::MAP_CHARACTER_ERROR = 0;
string Game_Constants::MAP_CHARACTER_ERROR_MATERIAL = "";
string Game_Constants::MAP_CHARACTER_ERROR_COLOR = "";
bool Game_Constants::MAP_CHARACTER_ERROR_SOLID = false;
bool Game_Constants::MAP_CHARACTER_ERROR_OPAQUE = false;
uint8_t Game_Constants::MAP_CHARACTER_PADDING = 0;
string Game_Constants::MAP_CHARACTER_PADDING_MATERIAL = "";
string Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR = "";
bool Game_Constants::MAP_CHARACTER_PADDING_SOLID = false;
bool Game_Constants::MAP_CHARACTER_PADDING_OPAQUE = false;
string Game_Constants::DISPLAY_FONT = "";
int32_t Game_Constants::CREATURE_COLLISION_REDUCTION = 0;
int32_t Game_Constants::CREATURE_COLLISION_STEPS = 0;
string Game_Constants::INITIAL_MAP = "";
int32_t Game_Constants::TILE_LIGHT_SOURCE_CHECK_PADDING = 0;
int16_t Game_Constants::MAXIMUM_LIGHT_LEVEL = 0;
int16_t Game_Constants::MINIMUM_LIGHT_LEVEL = 0;
double Game_Constants::MINIMUM_LIGHT_REDUCTION = 0.0;
int32_t Game_Constants::MINIMUM_LIGHT_RANGE = 0;
int32_t Game_Constants::MAXIMUM_LIGHT_RANGE = 0;
double Game_Constants::CREATURE_LIGHT_LEVEL_MAXIMUM = 0.0;
int32_t Game_Constants::MAXIMUM_TEXT_PARSER_LENGTH = 0;
string Game_Constants::TEXT_PARSER_FONT = "";
string Game_Constants::TEXT_DISPLAY_FONT = "";
int32_t Game_Constants::TEXT_DISPLAY_HEIGHT = 0;
int32_t Game_Constants::TEXT_DISPLAY_TIMEOUT = 0;
uint32_t Game_Constants::MAXIMUM_TEXT_DISPLAY_LINES = 0;

// END SCRIPT-GENERATED CONSTANT INITIALIZATIONS
void Game_Constants_Loader::set_game_constant (string name, string value) {
    if (name == "zoom_rate") {
        Engine_Data::ZOOM_RATE = Strings::string_to_double(value);
    } else if (name == "zoom_min") {
        Engine_Data::ZOOM_MIN = Strings::string_to_double(value);
    } else if (name == "zoom_max") {
        Engine_Data::ZOOM_MAX = Strings::string_to_double(value);
    }
    // BEGIN SCRIPT-GENERATED CONSTANT SETUP
    else if (name == "map_padding") {
        Game_Constants::MAP_PADDING = Strings::string_to_long(value);
    } else if (name == "map_character_error") {
        Game_Constants::MAP_CHARACTER_ERROR = Strings::string_to_unsigned_long(value);
    } else if (name == "map_character_error_material") {
        Game_Constants::MAP_CHARACTER_ERROR_MATERIAL = value;
    } else if (name == "map_character_error_color") {
        Game_Constants::MAP_CHARACTER_ERROR_COLOR = value;
    } else if (name == "map_character_error_solid") {
        Game_Constants::MAP_CHARACTER_ERROR_SOLID = Strings::string_to_bool(value);
    } else if (name == "map_character_error_opaque") {
        Game_Constants::MAP_CHARACTER_ERROR_OPAQUE = Strings::string_to_bool(value);
    } else if (name == "map_character_padding") {
        Game_Constants::MAP_CHARACTER_PADDING = Strings::string_to_unsigned_long(value);
    } else if (name == "map_character_padding_material") {
        Game_Constants::MAP_CHARACTER_PADDING_MATERIAL = value;
    } else if (name == "map_character_padding_background_color") {
        Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR = value;
    } else if (name == "map_character_padding_solid") {
        Game_Constants::MAP_CHARACTER_PADDING_SOLID = Strings::string_to_bool(value);
    } else if (name == "map_character_padding_opaque") {
        Game_Constants::MAP_CHARACTER_PADDING_OPAQUE = Strings::string_to_bool(value);
    } else if (name == "display_font") {
        Game_Constants::DISPLAY_FONT = value;
    } else if (name == "creature_collision_reduction") {
        Game_Constants::CREATURE_COLLISION_REDUCTION = Strings::string_to_long(value);
    } else if (name == "creature_collision_steps") {
        Game_Constants::CREATURE_COLLISION_STEPS = Strings::string_to_long(value);
    } else if (name == "initial_map") {
        Game_Constants::INITIAL_MAP = value;
    } else if (name == "tile_light_source_check_padding") {
        Game_Constants::TILE_LIGHT_SOURCE_CHECK_PADDING = Strings::string_to_long(value);
    } else if (name == "maximum_light_level") {
        Game_Constants::MAXIMUM_LIGHT_LEVEL = Strings::string_to_long(value);
    } else if (name == "minimum_light_level") {
        Game_Constants::MINIMUM_LIGHT_LEVEL = Strings::string_to_long(value);
    } else if (name == "minimum_light_reduction") {
        Game_Constants::MINIMUM_LIGHT_REDUCTION = Strings::string_to_double(value);
    } else if (name == "minimum_light_range") {
        Game_Constants::MINIMUM_LIGHT_RANGE = Strings::string_to_long(value);
    } else if (name == "maximum_light_range") {
        Game_Constants::MAXIMUM_LIGHT_RANGE = Strings::string_to_long(value);
    } else if (name == "creature_light_level_maximum") {
        Game_Constants::CREATURE_LIGHT_LEVEL_MAXIMUM = Strings::string_to_double(value);
    } else if (name == "maximum_text_parser_length") {
        Game_Constants::MAXIMUM_TEXT_PARSER_LENGTH = Strings::string_to_long(value);
    } else if (name == "text_parser_font") {
        Game_Constants::TEXT_PARSER_FONT = value;
    } else if (name == "text_display_font") {
        Game_Constants::TEXT_DISPLAY_FONT = value;
    } else if (name == "text_display_height") {
        Game_Constants::TEXT_DISPLAY_HEIGHT = Strings::string_to_long(value);
    } else if (name == "text_display_timeout") {
        Game_Constants::TEXT_DISPLAY_TIMEOUT = Strings::string_to_long(value);
    } else if (name == "maximum_text_display_lines") {
        Game_Constants::MAXIMUM_TEXT_DISPLAY_LINES = Strings::string_to_unsigned_long(value);
    }

    // END SCRIPT-GENERATED CONSTANT SETUP
}
