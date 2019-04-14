/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef game_h
#define game_h

#include "tile.h"
#include "creature.h"

#include <coords.h>
#include <quadtree.h>

#include <libtcod/fov.hpp>

#include <cstdint>
#include <vector>
#include <string>

class Game {
    private:
        // tiles
        static std::int32_t worldWidth;
        // tiles
        static std::int32_t worldHeight;
        static std::vector<std::vector<Tile>> tiles;
        // creatures[0] represets the player
        static std::vector<Creature> creatures;
        static TCODMap* fieldOfViewMap;
        static void deleteFieldOfViewMap();
        static void createFieldOfViewMap();

    public:
        // tile coordinates
        static Coords<std::int32_t> getWorldDimensions();
        // pixel coordinates
        static Coords<std::int32_t> getWorldDimensionsPixels();
        static std::vector<std::vector<Tile>>& getTiles();
        static Creature& getPlayer();
        static void castLight(const Coords<std::int32_t>& tilePosition);
        static bool isInFov(const Coords<std::int32_t>& tilePosition);
        static void clear_world();
        static void generate_world();
        static void tick();
        static void ai();
        static void movement();
        static void events();
        static void animate();
        static void render();
        static void render_to_textures();
        static void update_background();
        static void render_background();
        static void playerThrust(const std::string& direction);
        static bool moveInputState(const std::string& direction);
};

#endif
