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
        // should be within [2, 15]
        std::int32_t range;
        // frames
        // a value < 0 disables glowing
        std::int32_t glowRateMin;
        // frames
        // a value < 0 disables glowing
        std::int32_t glowRateMax;

        LightTemplate ();
        std::int32_t getRandomGlow() const;
};

#endif
