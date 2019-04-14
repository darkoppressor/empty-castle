/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef lighting_h
#define lighting_h

#include <color.h>

#include <string>
#include <cstdint>

class Lighting {
    public:
        // lightLevel => [MINIMUM_LIGHT_LEVEL, MAXIMUM_LIGHT_LEVEL], where MAXIMUM_LIGHT_LEVEL is fully lit and
        // MINIMUM_LIGHT_LEVEL is fully dark
        static Color getColorDimmedByLightLevel(const std::string& initialColor, std::int16_t lightLevel);
        // lightLevel => [MINIMUM_LIGHT_LEVEL, MAXIMUM_LIGHT_LEVEL], where MAXIMUM_LIGHT_LEVEL is fully lit and
        // MINIMUM_LIGHT_LEVEL is fully dark
        static Color getColorDimmedByLightLevel(Color* initialColor, std::int16_t lightLevel);
};

#endif
