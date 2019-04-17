/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "material.h"
#include "game_constants.h"

using namespace std;

Material::Material () {
    name = "";
    characterColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
}
