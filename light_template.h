/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef light_template_h
#define light_template_h

#include <string>
#include <vector>

class LightTemplate {
    public:
        std::string name;
        // frames
        // a value < 0 disables flickering
        std::int32_t flickerRateMin;
        // frames
        // a value < 0 disables flickering
        std::int32_t flickerRateMax;
        // frames
        // a value < 0 disables glowing
        std::int32_t glowRateMin;
        // frames
        // a value < 0 disables glowing
        std::int32_t glowRateMax;
        std::vector<std::string> colors;

        LightTemplate ();
        std::string getRandomColor() const;
        std::int32_t getRandomGlow() const;
};

#endif
