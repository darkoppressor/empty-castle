/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "material.h"
#include "game_constants.h"

using namespace std;

Material::Material () {
    name = "";
    characterColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
}
