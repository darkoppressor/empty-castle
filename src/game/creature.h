/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef creature_h
#define creature_h

#include "creature_template.h"
#include "light_template.h"
#include "light_source.h"
#include "material.h"

#include <collision/coords.h>
#include <math/math_vector.h>
#include <collision/collision.h>
#include <color/color2.h>

#include <string>
#include <cstdint>
#include <vector>

class Creature: public LightSource {
    private:
        std::string type;
        Coords<double> position;
        Vector velocity;
        Vector force;

        // Ephemeral values:
        // alpha is used for brightness
        Color2 lightColor;

        // Derived from type:
        CreatureTemplate* getType() const;

        unsigned char getCharacter() const;

        Material* getMaterial() const;
        double getMoveForce() const;
        double getMass() const;
        double getMaximumSpeed() const;
        LightTemplate* getLightTemplate() const;

        // Derived from material
        std::string getCharacterColor() const;

        void stop();
        void brake();

    public:
        Creature (const std::string& type, const Coords<double>& position);

        // pixel box
        Collision_Rect<double> getBox() const;
        // tile coordinates
        Coords<std::int32_t> getTilePosition() const;
        // pixel box
        Collision_Rect<double> getCollisionBox() const;

        const Vector& getVelocity() const;

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
        bool tileCollision(const Coords<double>& oldPosition);

        void render() const;
};

#endif
