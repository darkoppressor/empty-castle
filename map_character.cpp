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
    backgroundColor = "";
    playerSpawn = false;
    doorTo = "";
    solid = Game_Constants::MAP_CHARACTER_ERROR_SOLID;
    opaque = Game_Constants::MAP_CHARACTER_ERROR_OPAQUE;
    light = "";
}

MapCharacter::MapCharacter (const MapCharacter& mapCharacter) {
    this->character = mapCharacter.character;
    this->displayCharacter = mapCharacter.displayCharacter;
    this->characterColor = mapCharacter.characterColor;
    this->backgroundColor = mapCharacter.backgroundColor;
    this->playerSpawn = mapCharacter.playerSpawn;
    this->doorTo = mapCharacter.doorTo;
    this->solid = mapCharacter.solid;
    this->opaque = mapCharacter.opaque;
    this->light = mapCharacter.light;
}
