/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "light_template.h"
#include "game.h"
#include "game_constants.h"

using namespace std;

LightTemplate::LightTemplate () {
    name = "";
    color = "white";
    range = Game_Constants::MINIMUM_LIGHT_RANGE;
    glowRateMin = -1;
    glowRateMax = -1;
}

int32_t LightTemplate::getRandomGlow () const {
    int32_t glow = Game::getRng().random_range(0u, 1u);

    if (Game::getRng().random_range(0u, 1u) == 0u) {
        return glow;
    } else {
        return -glow;
    }
}
