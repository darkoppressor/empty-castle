/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef lighting_h
#define lighting_h

#include "better_color.h"

#include <color.h>

#include <string>

class Lighting {
    public:
        static Color applyLightToColor(const std::string& initialColor, const BetterColor& lightColor);
        static Color applyLightToColor(Color* initialColor, const BetterColor& lightColor);
};

#endif
