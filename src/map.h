/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef map_h
#define map_h

#include "map_character.h"

#include <string>
#include <vector>

class Map {
    public:
        std::string name;
        std::vector<MapCharacter> mapCharacters;
        std::vector<std::vector<unsigned char>> tiles;

        Map ();
};

#endif
