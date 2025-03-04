/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

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
