/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "light_source.h"
#include "game.h"
#include "game_constants.h"

#include <engine.h>

using namespace std;

void LightSource::updateLightSource (LightTemplate* lightTemplate) {
    if (lightTemplate != 0) {
        if (lightTemplate->glowRateMin < 0 || lightTemplate->glowRateMax < 0) {
            if (glow == GLOW_NOT_UPDATED) {
                glow = lightTemplate->getRandomGlow();
            }
        } else if (--glowCounter < 0) {
            glowCounter = (Game::getRng().random_range(lightTemplate->glowRateMin,
                                                       lightTemplate->glowRateMax) / 1000u) * Engine::UPDATE_RATE;

            glow = lightTemplate->getRandomGlow();
        }
    }
}

int32_t LightSource::getLightRange (LightTemplate* lightTemplate) const {
    return (lightTemplate != 0 ? lightTemplate->range : Game_Constants::MINIMUM_LIGHT_RANGE) + (glow !=
                                                                                                GLOW_NOT_UPDATED ?
                                                                                                glow : 0);
}

LightSource::LightSource () {
    glowCounter = 0;
    glow = GLOW_NOT_UPDATED;
}

string LightSource::getColor (LightTemplate* lightTemplate) {
    return lightTemplate != 0 ? lightTemplate->color : "white";
}
