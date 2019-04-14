/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "tile.h"
#include "game_constants.h"
#include "game.h"

#include <font.h>
#include <object_manager.h>
#include <game_manager.h>
#include <render.h>

using namespace std;

Tile::Tile () {
    character = Game_Constants::MAP_CHARACTER_ERROR;
    characterColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
    backgroundColor = "";
    characterUnseenColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
    backgroundUnseenColor = "";
    playerSpawn = false;
    doorTo = "";
    solid = Game_Constants::MAP_CHARACTER_ERROR_SOLID;
    opaque = Game_Constants::MAP_CHARACTER_ERROR_OPAQUE;
    lightSource = false;
    explored = false;
    seen = false;
}

void Tile::readFromMap (const vector<MapCharacter>& mapCharacters, unsigned char character) {
    for (const auto& mapCharacter : mapCharacters) {
        if (mapCharacter.character == character) {
            this->character = mapCharacter.displayCharacter;
            characterColor = mapCharacter.characterColor;
            backgroundColor = mapCharacter.backgroundColor;
            characterUnseenColor = mapCharacter.characterUnseenColor;
            backgroundUnseenColor = mapCharacter.backgroundUnseenColor;
            playerSpawn = mapCharacter.playerSpawn;
            doorTo = mapCharacter.doorTo;
            solid = mapCharacter.solid;
            opaque = mapCharacter.opaque;
            lightSource = mapCharacter.lightSource;

            return;
        }
    }
}

void Tile::setToPadding () {
    character = Game_Constants::MAP_CHARACTER_PADDING;
    characterColor = Game_Constants::MAP_CHARACTER_PADDING_COLOR;
    backgroundColor = Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR;
    characterUnseenColor = Game_Constants::MAP_CHARACTER_PADDING_COLOR;
    backgroundUnseenColor = Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR;
    solid = Game_Constants::MAP_CHARACTER_PADDING_SOLID;
    opaque = Game_Constants::MAP_CHARACTER_PADDING_OPAQUE;
}

Collision_Rect<int32_t> Tile::getBox (const Coords<int32_t>& tilePosition) {
    Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

    return Collision_Rect<int32_t>(
        tilePosition.x * (int32_t) font->get_letter_width(), tilePosition.y * (int32_t) font->get_letter_height(),
        (int32_t) font->get_letter_width(), (int32_t) font->get_letter_height());
}

bool Tile::isPlayerSpawn () const {
    return playerSpawn;
}

string Tile::getDoorTo () const {
    return doorTo;
}

bool Tile::isSolid () const {
    return solid;
}

bool Tile::isOpaque () const {
    return opaque;
}

bool Tile::isLightSource () const {
    return lightSource;
}

void Tile::setExplored (bool explored) {
    this->explored = explored;
}

bool Tile::isSeen () const {
    return seen;
}

void Tile::setSeen (bool seen) {
    this->seen = seen;
}

void Tile::render (const Coords<int32_t>& tilePosition) const {
    Collision_Rect<int32_t> box = getBox(tilePosition);
    Collision_Rect<double> boxRender(box.x, box.y, box.w, box.h);

    if (Collision::check_rect(boxRender * Game_Manager::camera_zoom, Game_Manager::camera)) {
        if (explored) {
            Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

            if (seen) {
                if (backgroundColor.length() > 0 && backgroundColor != "background") {
                    Render::render_rectangle(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                                             box.y * Game_Manager::camera_zoom - Game_Manager::camera.y,
                                             box.w * Game_Manager::camera_zoom, box.h * Game_Manager::camera_zoom, 1.0,
                                             backgroundColor);
                }

                font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                           box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1,
                                                                                              character), characterColor, 1.0, Game_Manager::camera_zoom,
                           Game_Manager::camera_zoom);
            } else {
                if (backgroundUnseenColor.length() > 0 && backgroundUnseenColor != "background") {
                    Render::render_rectangle(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                                             box.y * Game_Manager::camera_zoom - Game_Manager::camera.y,
                                             box.w * Game_Manager::camera_zoom, box.h * Game_Manager::camera_zoom, 1.0,
                                             backgroundUnseenColor);
                }

                font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                           box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1,
                                                                                              character), characterUnseenColor, 1.0, Game_Manager::camera_zoom,
                           Game_Manager::camera_zoom);
            }
        }
    }
}
