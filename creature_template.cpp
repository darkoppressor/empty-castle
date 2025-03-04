/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "creature_template.h"
#include "game_constants.h"

using namespace std;

CreatureTemplate::CreatureTemplate () {
    name = "";
    character = Game_Constants::MAP_CHARACTER_ERROR;
    material = Game_Constants::MAP_CHARACTER_ERROR_MATERIAL;
    moveForce = 0.0;
    mass = 0.0;
    maximumSpeed = 0.0;
    light = "";
}
