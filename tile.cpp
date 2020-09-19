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

const MapCharacter& Tile::getType () const {
    return Game::getMapCharacter(type);
}

unsigned char Tile::getCharacter () const {
    return getType().displayCharacter;
}

Material* Tile::getMaterial () const {
    return Game_Data::getMaterial(getType().material);
}

string Tile::getBackgroundColor () const {
    return getType().backgroundColor;
}

string Tile::getDoorTo () const {
    return getType().doorTo;
}

LightTemplate* Tile::getLightTemplate () const {
    if (getType().light.length() > 0) {
        return Game_Data::getLightTemplate(getType().light);
    } else {
        return 0;
    }
}

string Tile::getCharacterColor () const {
    return getMaterial()->characterColor;
}

Tile::Tile () {
    type = 0;
    explored = false;
}

bool Tile::isPlayerSpawn () const {
    return getType().playerSpawn;
}

bool Tile::isSolid () const {
    return getType().solid;
}

bool Tile::isOpaque () const {
    return getType().opaque;
}

Collision_Rect<double> Tile::getBox (const Coords<int32_t>& tilePosition) {
    Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

    return Collision_Rect<double>(
        tilePosition.x * (int32_t) font->get_letter_width(), tilePosition.y * (int32_t) font->get_letter_height(),
        (int32_t) font->get_letter_width(), (int32_t) font->get_letter_height());
}

void Tile::setType (uint32_t type) {
    this->type = type;
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
    return LightSource::getLightRange(getLightTemplate());
}

bool Tile::isLit () const {
    return lightColor.getAlpha() > 0;
}

Color2 Tile::getLightColor () const {
    return lightColor;
}

void Tile::clearLightColor () {
    appliedLightSources.clear();
    lightColor.clear();
}

void Tile::applyLight (uint32_t lightSourceId, int16_t lightLevel, const string& colorName) {
    if (!appliedLightSources.count(lightSourceId) && lightLevel > Game_Constants::MINIMUM_LIGHT_LEVEL &&
        colorName.length() > 0) {
        Color* color = Object_Manager::get_color(colorName);

        if (color != 0) {
            appliedLightSources.emplace(lightSourceId);

            double lightLevelFactor = (double) lightLevel / (double) Game_Constants::MAXIMUM_LIGHT_LEVEL;

            if (!isLit()) {
                lightColor.set(color->get_red() * lightLevelFactor,
                               color->get_green() * lightLevelFactor, color->get_blue() * lightLevelFactor, lightLevel);
            } else {
                lightColor.hdrAdd(color->get_red() * lightLevelFactor,
                                  color->get_green() * lightLevelFactor,
                                  color->get_blue() * lightLevelFactor, lightLevel);
            }
        }
    }
}

void Tile::render (const Coords<int32_t>& tilePosition) const {
    Collision_Rect<double> box = getBox(tilePosition);

    if (Collision::check_rect(box * Game_Manager::camera_zoom, Game_Manager::camera)) {
        if (explored) {
            if (getBackgroundColor().length() > 0 && getBackgroundColor() != "background") {
                Color finalBackgroundColor;
                Color* backgroundColorPtr = Object_Manager::get_color(getBackgroundColor());

                if (isLit()) {
                    finalBackgroundColor = Lighting::applyLightToColor(backgroundColorPtr, lightColor);
                } else {
                    finalBackgroundColor.set(backgroundColorPtr->get_red(),
                                             backgroundColorPtr->get_green(), backgroundColorPtr->get_blue(),
                                             backgroundColorPtr->get_alpha());
                }

                Render::render_rectangle(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                                         box.y * Game_Manager::camera_zoom - Game_Manager::camera.y,
                                         box.w * Game_Manager::camera_zoom, box.h * Game_Manager::camera_zoom, 1.0,
                                         &finalBackgroundColor);
            }

            Color finalCharacterColor = Lighting::applyLightToColor(getCharacterColor(), lightColor);
            Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

            font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                       box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1,
                                                                                          getCharacter()), &finalCharacterColor, 1.0, Game_Manager::camera_zoom,
                       Game_Manager::camera_zoom);
        }
    }
}
