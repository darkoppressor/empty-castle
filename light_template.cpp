/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "light_template.h"
#include "game.h"

using namespace std;

LightTemplate::LightTemplate () {
    name = "";
    flickerRateMin = -1;
    flickerRateMax = -1;
    glowRateMin = -1;
    glowRateMax = -1;
}

string LightTemplate::getRandomColor () const {
    if (colors.size() > 0) {
        return colors[Game::getRng().random_range(0, colors.size() - 1)];
    } else {
        return "";
    }
}

int32_t LightTemplate::getRandomGlow () const {
    int32_t glow = Game::getRng().random_range(0, 1);

    if (Game::getRng().random_range(0, 1) == 0) {
        return glow;
    } else {
        return -glow;
    }
}
