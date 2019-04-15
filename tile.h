/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef tile_h
#define tile_h

#include "map_character.h"
#include "light_template.h"
#include "light_source.h"
#include "better_color.h"

#include <collision.h>

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>

class Tile: public LightSource {
    private:
        unsigned char character;
        std::string characterColor;
        std::string backgroundColor;
        bool playerSpawn;
        std::string doorTo;
        bool solid;
        bool opaque;
        std::string light;

        // other saved values:
        bool explored;

        // ephemeral values:
        std::unordered_set<uint32_t> appliedLightSources;
        // alpha is used for brightness
        BetterColor lightColor;

        // getters:
        LightTemplate* getLightTemplate() const;

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

        void setExplored(bool explored);

        // Returns the light template for convenience
        LightTemplate* updateLightSource();
        std::int32_t getLightRange() const;

        // lighting:
        bool isLit() const;
        void clearLightColor();
        void applyLight(std::uint32_t lightSourceId, std::int16_t lightLevel, const std::string& colorName);

        void render(const Coords<std::int32_t>& tilePosition) const;
};

#endif
