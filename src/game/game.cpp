/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "game.h"
#include "game_data.h"
#include "game_constants.h"
#include "field_of_view.h"

#include <render/render.h>
#include <game_window.h>
#include <sound/sound_manager.h>
#include <game/game_manager.h>
#include <data/object_manager.h>
#include <log.h>
#include <engine.h>
#include <ui/button_events.h>
#include <data/object_manager.h>
#include <data/engine_data.h>
#include <strings/engine_strings.h>

using namespace std;

RNG Game::rng;
int32_t Game::worldWidth = 0;
int32_t Game::worldHeight = 0;
vector<MapCharacter> Game::mapCharacters;
vector<vector<Tile>> Game::tiles;
vector<Creature> Game::creatures;
TextParser Game::textParser;
TextDisplay Game::textDisplay;

RNG& Game::getRng () {
    return rng;
}

Coords<int32_t> Game::getWorldDimensions () {
    return Coords<int32_t>(worldWidth, worldHeight);
}

Coords<double> Game::getWorldDimensionsPixels () {
    Collision_Rect<double> tileBox = Tile::getBox(Coords<int32_t>(0, 0));

    return Coords<double>(worldWidth * tileBox.w, worldHeight * tileBox.h);
}

const MapCharacter& Game::getMapCharacter (uint32_t type) {
    if (type < mapCharacters.size()) {
        return mapCharacters[type];
    } else if (mapCharacters.size() > 0) {
        return mapCharacters[0];
    } else {
        Log::add_error("Error accessing map character with index '" + Strings::num_to_string(type) + "'");

        Engine::quit();
    }
}

vector<vector<Tile>>& Game::getTiles () {
    return tiles;
}

Creature& Game::getPlayer () {
    if (creatures.size() > 0) {
        return creatures[0];
    } else {
        Log::add_error("Error accessing player");

        Engine::quit();
    }
}

bool Game::isTextParserOn () {
    return textParser.isOn();
}

void Game::updateTextParserFocus () {
    textParser.updateFocus();
}

void Game::toggleTextParser (bool commit) {
    textParser.toggle(commit);
}

void Game::handleTextParserInputStates () {
    textParser.handleInputStates();
}

bool Game::handleTextParserInputEvents () {
    return textParser.handleInputEvents();
}

void Game::addDisplayText (const string& line) {
    textDisplay.add(line);
}

void Game::scrollTextDisplay (bool up) {
    textDisplay.scroll(up);
}

void Game::handleTextDisplayInputStates () {
    textDisplay.handleInputStates();
}

bool Game::handleTextDisplayInputEvents () {
    return textDisplay.handleInputEvents();
}

void Game::clear_world () {
    worldWidth = 0;
    worldHeight = 0;
    mapCharacters.clear();
    tiles.clear();
    creatures.clear();
    textParser.set(false);
    // TODO clear text display
}

void Game::generate_world () {
    clear_world();

    textParser.setup();
    textDisplay.setup(textParser.getHeight());

    RNG rngSeeder;

    rng.seed(rngSeeder.random_range(0, numeric_limits<uint32_t>::max()));

    Map* map = Game_Data::getMap(Game_Constants::INITIAL_MAP);

    mapCharacters.push_back(MapCharacter());

    MapCharacter padding;

    padding.character = Game_Constants::MAP_CHARACTER_PADDING;
    padding.displayCharacter = Game_Constants::MAP_CHARACTER_PADDING;
    padding.material = Game_Constants::MAP_CHARACTER_PADDING_MATERIAL;
    padding.backgroundColor = Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR;
    padding.solid = Game_Constants::MAP_CHARACTER_PADDING_SOLID;
    padding.opaque = Game_Constants::MAP_CHARACTER_PADDING_OPAQUE;
    mapCharacters.push_back(padding);

    for (const auto& mapCharacter : map->mapCharacters) {
        mapCharacters.push_back(mapCharacter);
    }

    worldWidth = map->tiles.size() + Game_Constants::MAP_PADDING * 2;
    worldHeight = map->tiles[0].size() + Game_Constants::MAP_PADDING * 2;

    tiles.resize(worldWidth, vector<Tile>(worldHeight));

    for (int32_t x = 0; x < worldWidth; x++) {
        for (int32_t y = 0; y < worldHeight; y++) {
            if (x < Game_Constants::MAP_PADDING || y < Game_Constants::MAP_PADDING ||
                x >= map->tiles.size() + Game_Constants::MAP_PADDING ||
                y >= map->tiles[0].size() + Game_Constants::MAP_PADDING) {
                tiles[x][y].setType(1);
            } else {
                uint32_t tileType = 0;

                for (uint32_t i = 0; i < mapCharacters.size(); i++) {
                    if (mapCharacters[i].character ==
                        map->tiles[x - Game_Constants::MAP_PADDING][y - Game_Constants::MAP_PADDING]) {
                        tileType = i;

                        break;
                    }
                }

                tiles[x][y].setType(tileType);

                if (creatures.size() == 0 && tiles[x][y].isPlayerSpawn()) {
                    Collision_Rect<double> tileBox = Tile::getBox(Coords<int32_t>(x, y));

                    creatures.push_back(Creature("player", Coords<double>(tileBox.x, tileBox.y)));
                }
            }
        }
    }

    if (creatures.size() == 0) {
        Log::add_error("No player spawned");

        Button_Events::handle_button_event("stop_game", 0);
    }
}

void Game::tick () {
}

void Game::ai () {
}

void Game::movement () {
    for (auto& creature : creatures) {
        creature.accelerate();
    }

    for (auto& creature : creatures) {
        creature.movement();
    }

    Collision_Rect<int32_t> cameraTileBox = getCameraTileBox(Game_Constants::TILE_LIGHT_SOURCE_CHECK_PADDING);

    FieldOfView::prepareToComputeFov(cameraTileBox, worldWidth, worldHeight, tiles);

    uint32_t lightSourceId = 0;

    for (int32_t x = cameraTileBox.x; x < cameraTileBox.w; x++) {
        for (int32_t y = cameraTileBox.y; y < cameraTileBox.h; y++) {
            if (x >= 0 && y >= 0 && x < worldWidth && y < worldHeight) {
                LightTemplate* light = tiles[x][y].updateLightSource();

                if (light != 0) {
                    FieldOfView::computeFov(worldWidth, worldHeight, tiles,
                                            FieldOfViewSource(Coords<int32_t>(x, y), tiles[x][y].getColor(light),
                                                              lightSourceId, tiles[x][y].getLightRange()), true);
                    lightSourceId++;
                }
            }
        }
    }

    for (auto& creature : creatures) {
        LightTemplate* light = creature.updateLightSource();

        if (light != 0) {
            FieldOfView::computeFov(worldWidth, worldHeight, tiles,
                                    FieldOfViewSource(creature.getTilePosition(), creature.getColor(light),
                                                      lightSourceId, creature.getLightRange()), true);
            lightSourceId++;
        }
    }

    for (auto& creature : creatures) {
        creature.applyLight();
    }
}

void Game::events () {
    // Sound_Manager::set_listener(example_player.circle.x,example_player.circle.y,Game_Manager::camera_zoom);
}

void Game::animate () {
    textParser.animate();
    textDisplay.animate();
}

void Game::render () {
    Collision_Rect<int32_t> cameraTileBox = getCameraTileBox(0);

    // Render each on-screen tile
    for (int32_t x = cameraTileBox.x; x < cameraTileBox.w; x++) {
        for (int32_t y = cameraTileBox.y; y < cameraTileBox.h; y++) {
            if (x >= 0 && y >= 0 && x < worldWidth && y < worldHeight) {
                tiles[x][y].render(Coords<int32_t>(x, y));
            }
        }
    }

    for (const auto& creature : creatures) {
        creature.render();
    }

    textParser.render();
    textDisplay.render();
}

void Game::render_to_textures () {
    /**Rtt_Manager::set_render_target("example");
       // Render something here Rtt_Manager::reset_render_target();*/
}

void Game::update_background () {
}

void Game::render_background () {
    Render::render_rectangle(0.0, 0.0, Game_Window::width(), Game_Window::height(), 1.0, "background");
}

Collision_Rect<int32_t> Game::getCameraTileBox (int32_t padding) {
    Collision_Rect<double> tileBox = Tile::getBox(Coords<int32_t>(0, 0));
    int32_t cameraTileX = (int32_t) (Game_Manager::camera.x / (tileBox.w * Game_Manager::camera_zoom));
    int32_t cameraTileY = (int32_t) (Game_Manager::camera.y / (tileBox.h * Game_Manager::camera_zoom));
    int32_t endTileX = cameraTileX + (int32_t) (Game_Manager::camera.w / (tileBox.w * Game_Manager::camera_zoom)) + 2;
    int32_t endTileY = cameraTileY + (int32_t) (Game_Manager::camera.h / (tileBox.h * Game_Manager::camera_zoom)) + 2;

    return Collision_Rect<int32_t>(cameraTileX - padding, cameraTileY - padding, endTileX + padding,
                                   endTileY + padding);
}

void Game::playerThrust (const string& direction) {
    getPlayer().setThrustAngle(direction);
}

bool Game::moveInputState (const string& direction) {
    if (Object_Manager::game_command_state(direction)) {
        return true;
    } else if (Object_Manager::game_command_state(direction + "_secondary")) {
        return true;
    }

    if (direction == "up" &&
        Object_Manager::game_command_state("move_stick_vertical") < -Engine_Data::controller_dead_zone) {
        return true;
    } else if (direction == "down" &&
               Object_Manager::game_command_state("move_stick_vertical") > Engine_Data::controller_dead_zone) {
        return true;
    } else if (direction == "left" &&
               Object_Manager::game_command_state("move_stick_horizontal") < -Engine_Data::controller_dead_zone) {
        return true;
    } else if (direction == "right" &&
               Object_Manager::game_command_state("move_stick_horizontal") > Engine_Data::controller_dead_zone) {
        return true;
    }

    return false;
}
