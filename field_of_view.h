/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */
/* This file incorporates code from libtcod. See the file docs/third-party-licenses/libtcod.txt. */

#ifndef field_of_view_h
#define field_of_view_h

#include "tile.h"

#include <coords.h>
#include <collision.h>

#include <vector>
#include <cstdint>
#include <string>

class FieldOfView {
    private:
        static std::int32_t maximum(std::int32_t a, std::int32_t b);
        static std::int32_t minimum(std::int32_t a, std::int32_t b);
        static std::int16_t getLightLevel(std::int32_t radius, std::int32_t maximumRadius);
        static void castRay(std::int32_t worldWidth, std::int32_t worldHeight, std::vector<std::vector<Tile>>& tiles,
                            const std::string& lightColor, std::int32_t xo, std::int32_t yo, std::int32_t xd,
                            std::int32_t yd, std::int32_t r2, bool lightWalls);
        static void postProcess(std::int32_t worldWidth, std::int32_t worldHeight,
                                std::vector<std::vector<Tile>>& tiles, const Coords<std::int32_t>& sourcePosition,
                                const std::string& lightColor, std::int32_t r2, std::int32_t x0, std::int32_t y0,
                                std::int32_t x1, std::int32_t y1, std::int32_t dx, std::int32_t dy);

    public:
        static void prepareToComputeFov(const Collision_Rect<std::int32_t>& cameraTileBox, std::int32_t worldWidth,
                                        std::int32_t worldHeight, std::vector<std::vector<Tile>>& tiles);
        static void computeFov(std::int32_t worldWidth, std::int32_t worldHeight, std::vector<std::vector<Tile>>& tiles,
                               const Coords<std::int32_t>& sourcePosition, const std::string& lightColor,
                               std::int32_t maxRadius, bool lightWalls);
};

#endif
