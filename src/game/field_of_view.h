/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */
/* This file incorporates code from libtcod. See the file docs/thirdPartyLicenses/libtcod.txt. */

#ifndef field_of_view_h
#define field_of_view_h

#include "tile.h"
#include "field_of_view_source.h"

#include <collision/coords.h>
#include <collision/collision.h>

#include <vector>
#include <cstdint>
#include <string>

class FieldOfView {
    private:
        static std::int32_t maximum(std::int32_t a, std::int32_t b);
        static std::int32_t minimum(std::int32_t a, std::int32_t b);
        static std::int16_t getLightLevel(std::int32_t radius, std::int32_t maximumRadius);
        static void castRay(std::int32_t worldWidth, std::int32_t worldHeight, std::vector<std::vector<Tile>>& tiles,
                            const FieldOfViewSource& source, std::int32_t xo, std::int32_t yo, std::int32_t xd,
                            std::int32_t yd, std::int32_t r2, bool lightWalls);
        static void postProcess(std::int32_t worldWidth, std::int32_t worldHeight,
                                std::vector<std::vector<Tile>>& tiles, const FieldOfViewSource& source, std::int32_t r2,
                                std::int32_t x0, std::int32_t y0, std::int32_t x1, std::int32_t y1, std::int32_t dx,
                                std::int32_t dy);

    public:
        static void prepareToComputeFov(const Collision_Rect<std::int32_t>& cameraTileBox, std::int32_t worldWidth,
                                        std::int32_t worldHeight, std::vector<std::vector<Tile>>& tiles);
        static void computeFov(std::int32_t worldWidth, std::int32_t worldHeight, std::vector<std::vector<Tile>>& tiles,
                               const FieldOfViewSource& source, bool lightWalls);
};

#endif
