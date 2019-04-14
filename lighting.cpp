/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "lighting.h"
#include "game_constants.h"

#include <object_manager.h>

using namespace std;

Color Lighting::getColorDimmedByLightLevel (const string& initialColor, int16_t lightLevel) {
    return getColorDimmedByLightLevel(Object_Manager::get_color(initialColor), lightLevel);
}

Color Lighting::getColorDimmedByLightLevel (Color* initialColor, int16_t lightLevel) {
    Color color = Color(initialColor->get_red(), initialColor->get_green(),
                        initialColor->get_blue(), initialColor->get_alpha());
    int16_t reduction = (Game_Constants::MAXIMUM_LIGHT_LEVEL - lightLevel) / Game_Constants::LIGHT_DIMMING_FACTOR;

    color.set((int16_t) (color.get_red() - reduction), (int16_t) (color.get_green() - reduction),
              (int16_t) (color.get_blue() - reduction), (int16_t) color.get_alpha());

    return color;
}
