/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "light_source.h"
#include "game.h"

using namespace std;

void LightSource::updateLightSource (LightTemplate* lightTemplate) {
    if (lightTemplate != 0) {
        if (lightTemplate->flickerRateMin < 0 || lightTemplate->flickerRateMax < 0) {
            if (lightSourceColor.length() == 0) {
                lightSourceColor = lightTemplate->getRandomColor();
            }
        } else if (--flickerCounter < 0) {
            flickerCounter = Game::getRng().random_range(lightTemplate->flickerRateMin, lightTemplate->flickerRateMax);

            lightSourceColor = lightTemplate->getRandomColor();
        }

        if (lightTemplate->glowRateMin < 0 || lightTemplate->glowRateMax < 0) {
            if (glow == -127) {
                glow = lightTemplate->getRandomGlow();
            }
        } else if (--glowCounter < 0) {
            glowCounter = Game::getRng().random_range(lightTemplate->glowRateMin, lightTemplate->glowRateMax);

            glow = lightTemplate->getRandomGlow();
        }
    }
}

int32_t LightSource::getLightRange (int32_t baseRange) const {
    return baseRange + (glow != -127 ? glow : 0);
}

LightSource::LightSource () {
    flickerCounter = 0;
    glowCounter = 0;
    glow = -127;
    lightSourceColor = "";
}

string LightSource::getLightSourceColor () const {
    return lightSourceColor;
}
