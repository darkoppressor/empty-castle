/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

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
