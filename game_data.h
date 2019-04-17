/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef game_data_h
#define game_data_h

#include "map.h"
#include "creature_template.h"
#include "light_template.h"
#include "material.h"

#include <progress_bar.h>
#include <file_io.h>

#include <vector>

class Game_Data {
    private:
        static std::vector<Map> maps;
        static std::vector<CreatureTemplate> creatureTemplates;
        static std::vector<LightTemplate> lightTemplates;
        static std::vector<Material> materials;

    public:
        // The total number of progress bar items in load_data_game()
        static const int game_data_load_item_count;
        static void load_data_game(Progress_Bar& bar);
        // Load any data of the passed tag type
        // Returns false if passed tag type's data could not be loaded
        // Returns true otherwise
        static void load_data_tag_game(std::string tag, File_IO_Load* load);
        static void unload_data_game();
        static void loadMap(File_IO_Load* load);
        static size_t loadMapCharacter(std::vector<std::string>& lines, size_t lineIndex);
        static size_t loadMapTiles(std::vector<std::string>& lines, size_t lineIndex);
        static Map* getMap(std::string name);
        static void loadCreatureTemplate(File_IO_Load* load);
        static CreatureTemplate* getCreatureTemplate(std::string name);
        static void loadLightTemplate(File_IO_Load* load);
        static LightTemplate* getLightTemplate(std::string name);
        static void loadMaterial(File_IO_Load* load);
        static Material* getMaterial(std::string name);
};

#endif
