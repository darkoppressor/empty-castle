/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef light_source_h
#define light_source_h

#include "light_template.h"

#include <cstdint>
#include <string>

class LightSource {
    private:
        static const std::int32_t GLOW_NOT_UPDATED = -127;

    protected:
        // ephemeral values:
        // frames
        std::int32_t glowCounter;
        // a value of GLOW_NOT_UPDATED indicates that glow has not yet been updated
        std::int32_t glow;

        void updateLightSource(LightTemplate* lightTemplate);
        std::int32_t getLightRange(LightTemplate* lightTemplate) const;

    public:
        LightSource ();

        static std::string getColor(LightTemplate* lightTemplate);
};

#endif
