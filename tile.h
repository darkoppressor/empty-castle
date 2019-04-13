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
        bool playerSpawn;
        std::string doorTo;
        bool solid;

    public:
        Tile ();

        void readFromMap(const std::vector<MapCharacter>& mapCharacters, unsigned char character);
        void setToPadding();

        // pixel box
        static Collision_Rect<std::int32_t> getBox(const Coords<std::uint32_t>& tilePosition);

        bool isPlayerSpawn() const;
        std::string getDoorTo() const;
        bool isSolid() const;

        void render(const Coords<std::uint32_t>& tilePosition) const;
};

#endif
