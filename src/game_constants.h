/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef game_constants_h
#define game_constants_h

#include <string>
#include <cstdint>

class Game_Constants {
    public:
        // BEGIN SCRIPT-GENERATED CONSTANT DECLARATIONS
        static std::int32_t MAP_PADDING;
        static std::uint8_t MAP_CHARACTER_ERROR;
        static std::string MAP_CHARACTER_ERROR_MATERIAL;
        static std::string MAP_CHARACTER_ERROR_COLOR;
        static bool MAP_CHARACTER_ERROR_SOLID;
        static bool MAP_CHARACTER_ERROR_OPAQUE;
        static std::uint8_t MAP_CHARACTER_PADDING;
        static std::string MAP_CHARACTER_PADDING_MATERIAL;
        static std::string MAP_CHARACTER_PADDING_BACKGROUND_COLOR;
        static bool MAP_CHARACTER_PADDING_SOLID;
        static bool MAP_CHARACTER_PADDING_OPAQUE;
        static std::string DISPLAY_FONT;
        static std::int32_t CREATURE_COLLISION_REDUCTION;
        static std::int32_t CREATURE_COLLISION_STEPS;
        static std::string INITIAL_MAP;
        static std::int32_t TILE_LIGHT_SOURCE_CHECK_PADDING;
        static std::int16_t MAXIMUM_LIGHT_LEVEL;
        static std::int16_t MINIMUM_LIGHT_LEVEL;
        static double MINIMUM_LIGHT_REDUCTION;
        static std::int32_t MINIMUM_LIGHT_RANGE;
        static std::int32_t MAXIMUM_LIGHT_RANGE;
        static double CREATURE_LIGHT_LEVEL_MAXIMUM;
        static std::int32_t MAXIMUM_TEXT_PARSER_LENGTH;
        static std::string TEXT_PARSER_FONT;
        static std::string TEXT_DISPLAY_FONT;
        static std::int32_t TEXT_DISPLAY_HEIGHT;
        static std::int32_t TEXT_DISPLAY_TIMEOUT;
        static std::uint32_t MAXIMUM_TEXT_DISPLAY_LINES;
        // END SCRIPT-GENERATED CONSTANT DECLARATIONS
};

#endif
