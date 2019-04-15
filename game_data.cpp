/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "game_data.h"
#include "game_constants.h"

#include <log.h>
#include <data_reader.h>
#include <data_manager.h>
#include <engine_strings.h>

#include <boost/algorithm/string.hpp>

using namespace std;

vector<Map> Game_Data::maps;
vector<CreatureTemplate> Game_Data::creatureTemplates;
vector<LightTemplate> Game_Data::lightTemplates;

///Don't forget to increment this for each progress item in load_data_game() below
const int Game_Data::game_data_load_item_count = 3;
void Game_Data::load_data_game (Progress_Bar& bar) {
    bar.progress("Loading maps");
    Data_Manager::load_data("map");

    bar.progress("Loading creature templates");
    Data_Manager::load_data("creature");

    bar.progress("Loading light templates");
    Data_Manager::load_data("light");
}

void Game_Data::load_data_tag_game (string tag, File_IO_Load* load) {
    if (tag == "map") {
        loadMap(load);
    } else if (tag == "creature") {
        loadCreatureTemplate(load);
    } else if (tag == "light") {
        loadLightTemplate(load);
    }
}

void Game_Data::unload_data_game () {
    maps.clear();
    creatureTemplates.clear();
    lightTemplates.clear();
}

void Game_Data::loadMap (File_IO_Load* load) {
    maps.push_back(Map());

    vector<string> lines = Data_Reader::read_data(load, "</map>");

    for (size_t i = 0; i < lines.size(); i++) {
        string& line = lines[i];

        if (Data_Reader::check_prefix(line, "name:")) {
            maps.back().name = line;
        } else if (Data_Reader::check_prefix(line, "<tiles>")) {
            i = loadMapTiles(lines, i + 1);
        } else if (Data_Reader::check_prefix(line, "<mapCharacter>")) {
            i = loadMapCharacter(lines, i + 1);
        }
    }
}

size_t Game_Data::loadMapCharacter (vector<string>& lines, size_t lineIndex) {
    maps.back().mapCharacters.push_back(MapCharacter());

    for (size_t i = lineIndex; i < lines.size(); i++) {
        string& line = lines[i];

        if (Data_Reader::check_prefix(line, "character:")) {
            maps.back().mapCharacters.back().character = line[0];
        } else if (Data_Reader::check_prefix(line, "displayCharacter:")) {
            if (boost::algorithm::starts_with(line, "'") && boost::algorithm::ends_with(line, "'")) {
                boost::algorithm::erase_first(line, "'");
                boost::algorithm::erase_last(line, "'");
                maps.back().mapCharacters.back().displayCharacter = line[0];
            } else {
                maps.back().mapCharacters.back().displayCharacter = (unsigned char) Strings::string_to_unsigned_long(
                    line);
            }
        } else if (Data_Reader::check_prefix(line, "characterColor:")) {
            maps.back().mapCharacters.back().characterColor = line;
        } else if (Data_Reader::check_prefix(line, "backgroundColor:")) {
            maps.back().mapCharacters.back().backgroundColor = line;
        } else if (Data_Reader::check_prefix(line, "<playerSpawn>")) {
            maps.back().mapCharacters.back().playerSpawn = true;
        } else if (Data_Reader::check_prefix(line, "doorTo:")) {
            maps.back().mapCharacters.back().doorTo = line;
        } else if (Data_Reader::check_prefix(line, "<solid>")) {
            maps.back().mapCharacters.back().solid = true;
        } else if (Data_Reader::check_prefix(line, "<opaque>")) {
            maps.back().mapCharacters.back().opaque = true;
        } else if (Data_Reader::check_prefix(line, "light:")) {
            maps.back().mapCharacters.back().light = line;
        } else if (Data_Reader::check_prefix(line, "</mapCharacter>")) {
            return i;
        }
    }

    return lines.size() - 1;
}

size_t Game_Data::loadMapTiles (vector<string>& lines, size_t lineIndex) {
    size_t tilesWidth = 0;
    size_t tilesHeight = 0;

    for (size_t i = lineIndex; i < lines.size(); i++) {
        string& line = lines[i];

        if (line.length() > 0) {
            if (boost::algorithm::starts_with(line, "</tiles>")) {
                break;
            } else {
                if (tilesWidth == 0) {
                    tilesWidth = line.length();
                }

                tilesHeight++;
            }
        }
    }

    vector<vector<unsigned char>> mapTiles;
    mapTiles.resize(tilesWidth, vector<unsigned char>(tilesHeight));

    for (size_t x = 0; x < tilesWidth; x++) {
        for (size_t y = 0; y < tilesHeight; y++) {
            mapTiles[x][y] = Game_Constants::MAP_CHARACTER_ERROR;
        }
    }

    for (size_t i = lineIndex, y = 0; i < lines.size(); i++) {
        string& line = lines[i];

        if (line.length() > 0) {
            if (Data_Reader::check_prefix(line, "</tiles>")) {
                maps.back().tiles = mapTiles;

                return i;
            } else {
                for (size_t x = 0; x < line.length(); x++) {
                    if (x < tilesWidth) {
                        mapTiles[x][y] = line[x];
                    } else {
                        break;
                    }
                }

                y++;
            }
        }
    }

    return lines.size() - 1;
}

Map* Game_Data::getMap (string name) {
    Map* ptr_object = 0;

    for (size_t i = 0; i < maps.size(); i++) {
        if (maps[i].name == name) {
            ptr_object = &maps[i];

            break;
        }
    }

    if (ptr_object == 0) {
        Log::add_error("Error accessing map '" + name + "'");
    }

    return ptr_object;
}

void Game_Data::loadCreatureTemplate (File_IO_Load* load) {
    creatureTemplates.push_back(CreatureTemplate());

    vector<string> lines = Data_Reader::read_data(load, "</creature>");

    for (size_t i = 0; i < lines.size(); i++) {
        string& line = lines[i];

        if (Data_Reader::check_prefix(line, "name:")) {
            creatureTemplates.back().name = line;
        } else if (Data_Reader::check_prefix(line, "character:")) {
            if (boost::algorithm::starts_with(line, "'") && boost::algorithm::ends_with(line, "'")) {
                boost::algorithm::erase_first(line, "'");
                boost::algorithm::erase_last(line, "'");
                creatureTemplates.back().character = line[0];
            } else {
                creatureTemplates.back().character = (unsigned char) Strings::string_to_unsigned_long(line);
            }
        } else if (Data_Reader::check_prefix(line, "characterColor:")) {
            creatureTemplates.back().characterColor = line;
        } else if (Data_Reader::check_prefix(line, "moveForce:")) {
            creatureTemplates.back().moveForce = Strings::string_to_long(line);
        } else if (Data_Reader::check_prefix(line, "mass:")) {
            creatureTemplates.back().mass = Strings::string_to_long(line);
        } else if (Data_Reader::check_prefix(line, "maximumSpeed:")) {
            creatureTemplates.back().maximumSpeed = Strings::string_to_long(line);
        } else if (Data_Reader::check_prefix(line, "light:")) {
            creatureTemplates.back().light = line;
        }
    }
}

CreatureTemplate* Game_Data::getCreatureTemplate (string name) {
    CreatureTemplate* ptr_object = 0;

    for (size_t i = 0; i < creatureTemplates.size(); i++) {
        if (creatureTemplates[i].name == name) {
            ptr_object = &creatureTemplates[i];

            break;
        }
    }

    if (ptr_object == 0) {
        Log::add_error("Error accessing creature template '" + name + "'");
    }

    return ptr_object;
}

void Game_Data::loadLightTemplate (File_IO_Load* load) {
    lightTemplates.push_back(LightTemplate());

    vector<string> lines = Data_Reader::read_data(load, "</light>");

    for (size_t i = 0; i < lines.size(); i++) {
        string& line = lines[i];

        if (Data_Reader::check_prefix(line, "name:")) {
            lightTemplates.back().name = line;
        } else if (Data_Reader::check_prefix(line, "color:")) {
            lightTemplates.back().color = line;
        } else if (Data_Reader::check_prefix(line, "glowRateMin:")) {
            lightTemplates.back().glowRateMin = Strings::string_to_long(line);
        } else if (Data_Reader::check_prefix(line, "glowRateMax:")) {
            lightTemplates.back().glowRateMax = Strings::string_to_long(line);
        }
    }
}

LightTemplate* Game_Data::getLightTemplate (string name) {
    LightTemplate* ptr_object = 0;

    for (size_t i = 0; i < lightTemplates.size(); i++) {
        if (lightTemplates[i].name == name) {
            ptr_object = &lightTemplates[i];

            break;
        }
    }

    if (ptr_object == 0) {
        Log::add_error("Error accessing light template '" + name + "'");
    }

    return ptr_object;
}
