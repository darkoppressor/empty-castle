/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef light_source_h
#define light_source_h

#include "light_template.h"

#include <cstdint>
#include <string>

class LightSource {
    protected:
        // ephemeral values:
        // frames
        std::int32_t flickerCounter;
        // frames
        std::int32_t glowCounter;
        // a value of -127 indicates that glow has not yet been updated
        std::int32_t glow;
        std::string lightSourceColor;

        void updateLightSource(LightTemplate* lightTemplate);
        std::int32_t getLightRange(std::int32_t baseRange) const;

    public:
        LightSource ();
        std::string getLightSourceColor() const;
};

#endif
