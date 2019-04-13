/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef map_h
#define map_h

#include "map_character.h"

#include <string>
#include <vector>

class Map {
    public:
        std::string name;
        std::uint32_t padding;
        std::vector<MapCharacter> mapCharacters;
        std::vector<std::vector<unsigned char>> tiles;

        Map ();
};

#endif
