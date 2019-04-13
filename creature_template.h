/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef creature_template_h
#define creature_template_h

#include <string>

class CreatureTemplate {
    public:
        std::string name;
        unsigned char character;
        std::string characterColor;
        // newtons
        // Note that this should be > mass, because a force smaller than mass will be rounded down to 0
        // acceleration
        std::int32_t moveForce;
        // kilograms
        std::int32_t mass;
        // meters/second
        // Note that this needs to be >= the logic update rate, because speeds below it are rounded down to 0
        std::int32_t maximumSpeed;

        CreatureTemplate ();
};

#endif
