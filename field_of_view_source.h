/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */
/* This file incorporates code from libtcod. See the file docs/third-party-licenses/libtcod.txt. */

#ifndef field_of_view_source_h
#define field_of_view_source_h

#include <coords.h>

#include <cstdint>
#include <string>

class FieldOfViewSource {
    private:
        Coords<std::int32_t> sourcePosition;
        std::string lightColor;
        std::uint32_t lightSourceId;
        std::int32_t maximumRadius;

    public:
        FieldOfViewSource (const Coords<std::int32_t>& sourcePosition, const std::string& lightColor,
                           std::uint32_t lightSourceId, std::int32_t maximumRadius);

        Coords<std::int32_t> getSourcePosition() const;
        std::string getLightColor() const;
        std::uint32_t getLightSourceId() const;
        std::int32_t getMaximumRadius() const;
};

#endif
