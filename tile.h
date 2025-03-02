/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef tile_h
#define tile_h

#include "map_character.h"
#include "light_template.h"
#include "light_source.h"
#include "material.h"

#include <collision.h>
#include <color2.h>

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_set>

class Tile: public LightSource {
    private:
        std::uint32_t type;
        bool explored;

        // Ephemeral values:
        std::unordered_set<uint32_t> appliedLightSources;
        // alpha is used for brightness
        Color2 lightColor;

        // Derived from type:
        const MapCharacter& getType() const;

        unsigned char getCharacter() const;

        Material* getMaterial() const;
        std::string getBackgroundColor() const;
        std::string getDoorTo() const;
        LightTemplate* getLightTemplate() const;

        // Derived from material:
        std::string getCharacterColor() const;

    public:
        Tile ();

        // Derived from type:
        bool isPlayerSpawn() const;
        bool isSolid() const;
        bool isOpaque() const;

        // pixel box
        static Collision_Rect<double> getBox(const Coords<std::int32_t>& tilePosition);

        void setType(std::uint32_t type);
        void setExplored(bool explored);

        // light source:
        // Returns the light template for convenience
        LightTemplate* updateLightSource();
        std::int32_t getLightRange() const;

        // lighting:
        bool isLit() const;
        Color2 getLightColor() const;
        void clearLightColor();
        void applyLight(std::uint32_t lightSourceId, std::int16_t lightLevel, const std::string& colorName);

        void render(const Coords<std::int32_t>& tilePosition) const;
};

#endif
