/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef creature_h
#define creature_h

#include "creature_template.h"

#include <coords.h>
#include <int_vector.h>
#include <collision.h>

#include <string>
#include <cstdint>
#include <vector>

class Creature {
    private:
        std::string type;
        Coords<std::int32_t> position;
        Int_Vector velocity;
        Int_Vector force;
        CreatureTemplate* getType() const;
        unsigned char getCharacter() const;
        std::string getCharacterColor() const;
        std::int32_t getMoveForce() const;
        std::int32_t getMass() const;
        std::int32_t getMaximumSpeed() const;

    public:
        Creature (const std::string& type, const Coords<std::int32_t>& position);

        // pixel box
        Collision_Rect<std::int32_t> getBox() const;
        // tile coordinates
        Coords<std::int32_t> getTilePosition() const;
        // pixel box
        Collision_Rect<std::int32_t> getCollisionBox() const;

        bool isAlive() const;

        void setThrustAngle(const std::string& direction);
        void brake();
        void accelerate();
        void movement();
        // Returns true if collision detected
        bool tileCollision(const Coords<std::int32_t>& oldPosition);

        void render() const;
};

#endif
