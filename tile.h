/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef tile_h
#define tile_h

#include "map_character.h"

#include <collision.h>

#include <string>
#include <vector>
#include <cstdint>

class Tile {
    private:
        unsigned char character;
        std::string characterColor;
        std::string backgroundColor;
        std::string characterUnseenColor;
        std::string backgroundUnseenColor;
        bool playerSpawn;
        std::string doorTo;
        bool solid;
        bool opaque;
        bool lightSource;

        // other saved values:
        bool explored;

        // ephemeral values:
        bool seen;

    public:
        Tile ();

        void readFromMap(const std::vector<MapCharacter>& mapCharacters, unsigned char character);
        void setToPadding();

        // pixel box
        static Collision_Rect<std::int32_t> getBox(const Coords<std::int32_t>& tilePosition);

        bool isPlayerSpawn() const;
        std::string getDoorTo() const;
        bool isSolid() const;
        bool isOpaque() const;
        bool isLightSource() const;

        void setExplored(bool explored);

        bool isSeen() const;
        void setSeen(bool seen);

        void render(const Coords<std::int32_t>& tilePosition) const;
};

#endif
