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
    backgroundColor = Game_Constants::MAP_CHARACTER_ERROR_BACKGROUND_COLOR;
    playerSpawn = false;
    doorTo = "";
    solid = Game_Constants::MAP_CHARACTER_ERROR_SOLID;
    opaque = Game_Constants::MAP_CHARACTER_ERROR_OPAQUE;
}

void Tile::readFromMap (const vector<MapCharacter>& mapCharacters, unsigned char character) {
    for (const auto& mapCharacter : mapCharacters) {
        if (mapCharacter.character == character) {
            this->character = mapCharacter.displayCharacter;
            characterColor = mapCharacter.characterColor;
            backgroundColor = mapCharacter.backgroundColor;
            playerSpawn = mapCharacter.playerSpawn;
            doorTo = mapCharacter.doorTo;
            solid = mapCharacter.solid;
            opaque = mapCharacter.opaque;

            return;
        }
    }
}

void Tile::setToPadding () {
    character = Game_Constants::MAP_CHARACTER_PADDING;
    characterColor = Game_Constants::MAP_CHARACTER_PADDING_COLOR;
    backgroundColor = Game_Constants::MAP_CHARACTER_PADDING_BACKGROUND_COLOR;
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

void Tile::render (const Coords<int32_t>& tilePosition) const {
    Collision_Rect<int32_t> box = getBox(tilePosition);
    Collision_Rect<double> boxRender(box.x, box.y, box.w, box.h);

    if (Collision::check_rect(boxRender * Game_Manager::camera_zoom, Game_Manager::camera)) {
        if (Game::isInFov(tilePosition)) {
            if (backgroundColor != "background_color") {
                Render::render_rectangle(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                                         box.y * Game_Manager::camera_zoom - Game_Manager::camera.y,
                                         box.w * Game_Manager::camera_zoom, box.h * Game_Manager::camera_zoom, 1.0,
                                         backgroundColor);
            }

            Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

            font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                       box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1,
                                                                                          character), characterColor, 1.0, Game_Manager::camera_zoom,
                       Game_Manager::camera_zoom);
        } else {
            Render::render_rectangle(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                                     box.y * Game_Manager::camera_zoom - Game_Manager::camera.y,
                                     box.w * Game_Manager::camera_zoom, box.h * Game_Manager::camera_zoom, 1.0,
                                     "fog_of_war");
        }
    }
}
