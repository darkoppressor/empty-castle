/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef creature_template_h
#define creature_template_h

#include <string>

class CreatureTemplate {
    public:
        std::string name;
        unsigned char character;
        std::string material;
        // newtons
        double moveForce;
        // kilograms
        double mass;
        // meters/second
        double maximumSpeed;
        std::string light;

        CreatureTemplate ();
};

#endif
