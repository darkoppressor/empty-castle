/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "map_character.h"
#include "game_constants.h"

using namespace std;

MapCharacter::MapCharacter () {
    character = Game_Constants::MAP_CHARACTER_ERROR;
    displayCharacter = Game_Constants::MAP_CHARACTER_ERROR;
    characterColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
    backgroundColor = Game_Constants::MAP_CHARACTER_ERROR_BACKGROUND_COLOR;
    playerSpawn = false;
    doorTo = "";
    solid = Game_Constants::MAP_CHARACTER_ERROR_SOLID;
    opaque = Game_Constants::MAP_CHARACTER_ERROR_OPAQUE;
}
