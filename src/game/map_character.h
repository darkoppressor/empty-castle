/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef map_character_h
#define map_character_h

#include <string>

class MapCharacter {
    public:
        unsigned char character;
        unsigned char displayCharacter;
        std::string material;
        std::string backgroundColor;
        bool playerSpawn;
        std::string doorTo;
        bool solid;
        bool opaque;
        std::string light;

        MapCharacter ();
        MapCharacter (const MapCharacter& mapCharacter);
};

#endif
