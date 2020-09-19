/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "lighting.h"
#include "game_constants.h"

#include <object_manager.h>

using namespace std;

Color Lighting::applyLightToColor (const string& initialColor, const Color2& lightColor) {
    return applyLightToColor(Object_Manager::get_color(initialColor), lightColor);
}

Color Lighting::applyLightToColor (Color* initialColor, const Color2& lightColor) {
    Color2 baseColor(initialColor->get_red(), initialColor->get_green(), initialColor->get_blue(),
                     Color2::MINIMUM_CHANNEL_VALUE);

    if (lightColor.getAlpha() > 0) {
        baseColor.hdrAdd(lightColor.getRed(), lightColor.getGreen(), lightColor.getBlue(), lightColor.getAlpha());

        baseColor = baseColor.getHdrRescaled();
    }

    double reductionFactor = (double) lightColor.getAlpha() / (double) Game_Constants::MAXIMUM_LIGHT_LEVEL;

    if (reductionFactor < Game_Constants::MINIMUM_LIGHT_REDUCTION) {
        reductionFactor = Game_Constants::MINIMUM_LIGHT_REDUCTION;
    }

    return Color(baseColor.getRed() * reductionFactor, baseColor.getGreen() * reductionFactor,
                 baseColor.getBlue() * reductionFactor, initialColor->get_alpha());
}
