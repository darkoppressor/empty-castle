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
