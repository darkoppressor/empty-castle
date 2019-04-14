/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "creature_template.h"
#include "game_constants.h"

using namespace std;

CreatureTemplate::CreatureTemplate () {
    name = "";
    character = Game_Constants::MAP_CHARACTER_ERROR;
    characterColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
    moveForce = 0;
    mass = 0;
    maximumSpeed = 0;
    light = "";
}
