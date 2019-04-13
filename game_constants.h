/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef game_constants_h
#define game_constants_h

#include <string>
#include <cstdint>

class Game_Constants {
    public:
    /// BEGIN SCRIPT-GENERATED CONSTANT DECLARATIONS
    static std::uint8_t MAP_CHARACTER_ERROR;
    static std::string MAP_CHARACTER_ERROR_COLOR;
    static std::string MAP_CHARACTER_ERROR_BACKGROUND_COLOR;
    static bool MAP_CHARACTER_ERROR_SOLID;
    static std::uint8_t MAP_CHARACTER_PADDING;
    static std::string MAP_CHARACTER_PADDING_COLOR;
    static std::string MAP_CHARACTER_PADDING_BACKGROUND_COLOR;
    static bool MAP_CHARACTER_PADDING_SOLID;
    static std::string DISPLAY_FONT;
    static std::int32_t CREATURE_COLLISION_REDUCTION;
    static std::int32_t CREATURE_COLLISION_STEPS;
    /// END SCRIPT-GENERATED CONSTANT DECLARATIONS
};

#endif
