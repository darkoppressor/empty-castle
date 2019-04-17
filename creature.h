/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef creature_h
#define creature_h

#include "creature_template.h"
#include "light_template.h"
#include "light_source.h"
#include "better_color.h"
#include "material.h"

#include <coords.h>
#include <int_vector.h>
#include <collision.h>

#include <string>
#include <cstdint>
#include <vector>

class Creature: public LightSource {
    private:
        std::string type;
        Coords<std::int32_t> position;
        Int_Vector velocity;
        Int_Vector force;

        // Ephemeral values:
        // alpha is used for brightness
        BetterColor lightColor;

        // Derived from type:
        CreatureTemplate* getType() const;
        unsigned char getCharacter() const;
        Material* getMaterial() const;
        std::int32_t getMoveForce() const;
        std::int32_t getMass() const;
        std::int32_t getMaximumSpeed() const;
        LightTemplate* getLightTemplate() const;

        // Derived from material
        std::string getCharacterColor() const;

        void stop();
        void brake();

    public:
        Creature (const std::string& type, const Coords<std::int32_t>& position);

        // pixel box
        Collision_Rect<std::int32_t> getBox() const;
        // tile coordinates
        Coords<std::int32_t> getTilePosition() const;
        // pixel box
        Collision_Rect<std::int32_t> getCollisionBox() const;

        bool isAlive() const;

        // light source:
        // Returns the light template for convenience
        LightTemplate* updateLightSource();
        std::int32_t getLightRange() const;

        // lighting:
        bool isLit() const;
        void applyLight();

        void setThrustAngle(const std::string& direction);
        void accelerate();
        void movement();
        // Returns true if collision detected
        bool tileCollision(const Coords<std::int32_t>& oldPosition);

        void render() const;
};

#endif
