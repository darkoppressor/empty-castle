/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "map_character.h"
#include "game_constants.h"

using namespace std;

MapCharacter::MapCharacter () {
    character = Game_Constants::MAP_CHARACTER_ERROR;
    displayCharacter = Game_Constants::MAP_CHARACTER_ERROR;
    material = Game_Constants::MAP_CHARACTER_ERROR_MATERIAL;
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
    this->material = mapCharacter.material;
    this->backgroundColor = mapCharacter.backgroundColor;
    this->playerSpawn = mapCharacter.playerSpawn;
    this->doorTo = mapCharacter.doorTo;
    this->solid = mapCharacter.solid;
    this->opaque = mapCharacter.opaque;
    this->light = mapCharacter.light;
}
