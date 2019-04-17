/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef light_template_h
#define light_template_h

#include <string>

class LightTemplate {
    public:
        std::string name;
        std::string color;
        // tiles
        // should be within [MINIMUM_LIGHT_RANGE, MAXIMUM_LIGHT_RANGE]
        std::int32_t range;
        // ms
        // a value < 0 disables glowing
        std::int32_t glowRateMin;
        // ms
        // a value < 0 disables glowing
        std::int32_t glowRateMax;

        LightTemplate ();
        std::int32_t getRandomGlow() const;
};

#endif
