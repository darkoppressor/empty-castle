/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef lighting_h
#define lighting_h

#include <color.h>
#include <color2.h>

#include <string>

class Lighting {
    public:
        static Color applyLightToColor(const std::string& initialColor, const Color2& lightColor);
        static Color applyLightToColor(Color* initialColor, const Color2& lightColor);
};

#endif
