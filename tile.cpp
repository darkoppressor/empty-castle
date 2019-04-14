/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "tile.h"
#include "game_constants.h"
#include "game.h"
#include "lighting.h"
#include "game_data.h"

#include <font.h>
#include <object_manager.h>
#include <game_manager.h>
#include <render.h>

using namespace std;

LightTemplate* Tile::getLightTemplate () const {
    if (light.length() > 0) {
        return Game_Data::getLightTemplate(light);
    } else {
        return 0;
    }
}

Tile::Tile () {
    character = Game_Constants::MAP_CHARACTER_ERROR;
    characterColor = Game_Constants::MAP_CHARACTER_ERROR_COLOR;
    backgroundColor = "";
    playerSpawn = false;
    doorTo = "";
    solid = Game_Constants::MAP_CHARACTER_ERROR_SOLID;
    opaque = Game_Constants::MAP_CHARACTER_ERROR_OPAQUE;
    light = "";
    explored = false;
    lightLevel = Game_Constants::MINIMUM_LIGHT_LEVEL;
    lightColor = "";
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
            light = mapCharacter.light;

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

void Tile::setExplored (bool explored) {
    this->explored = explored;
}

LightTemplate* Tile::updateLightSource () {
    LightTemplate* lightTemplate = getLightTemplate();

    LightSource::updateLightSource(lightTemplate);

    return lightTemplate;
}

int32_t Tile::getLightRange () const {
    return LightSource::getLightRange(Game_Constants::TILE_LIGHT_RANGE);
}

int16_t Tile::getLightLevel () const {
    return lightLevel;
}

void Tile::setLightLevel (int16_t lightLevel) {
    this->lightLevel = lightLevel;
}

void Tile::applyLight (int16_t lightLevel, const string& color) {
    if (lightLevel > this->lightLevel) {
        this->lightLevel = lightLevel;
    }

    if (color.length() > 0 && (lightLevel > this->lightLevel || lightColor.length() == 0)) {
        lightColor = color;
    }
}

void Tile::clearLightColor () {
    lightColor = "";
}

void Tile::render (const Coords<int32_t>& tilePosition) const {
    Collision_Rect<int32_t> box = getBox(tilePosition);
    Collision_Rect<double> boxRender(box.x, box.y, box.w, box.h);

    if (Collision::check_rect(boxRender * Game_Manager::camera_zoom, Game_Manager::camera)) {
        if (explored) {
            Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);
            string backgroundColorToUse = lightColor;

            if (backgroundColorToUse.length() == 0) {
                backgroundColorToUse = backgroundColor;
            }

            if (backgroundColorToUse.length() > 0 && backgroundColorToUse != "background") {
                Color modifiedBackgroundColor = Lighting::getColorDimmedByLightLevel(backgroundColorToUse, lightLevel);

                Render::render_rectangle(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                                         box.y * Game_Manager::camera_zoom - Game_Manager::camera.y,
                                         box.w * Game_Manager::camera_zoom, box.h * Game_Manager::camera_zoom, 1.0,
                                         &modifiedBackgroundColor);
            }

            Color modifiedCharacterColor = Lighting::getColorDimmedByLightLevel(characterColor, lightLevel);

            font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                       box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1,
                                                                                          character), &modifiedCharacterColor, 1.0, Game_Manager::camera_zoom,
                       Game_Manager::camera_zoom);
        }
    }
}
