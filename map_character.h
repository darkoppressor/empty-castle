/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef map_character_h
#define map_character_h

#include <string>

class MapCharacter {
    public:
        unsigned char character;
        unsigned char displayCharacter;
        std::string characterColor;
        std::string backgroundColor;
        bool playerSpawn;
        std::string doorTo;
        bool solid;
        bool opaque;
        std::string light;

        MapCharacter ();
};

#endif
