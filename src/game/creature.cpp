/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "creature.h"
#include "game_constants.h"
#include "game_data.h"
#include "game.h"
#include "lighting.h"

#include <ui/font.h>
#include <data/object_manager.h>
#include <game/game_manager.h>
#include <engine.h>

using namespace std;

CreatureTemplate* Creature::getType () const {
    return Game_Data::getCreatureTemplate(type);
}

unsigned char Creature::getCharacter () const {
    return getType()->character;
}

Material* Creature::getMaterial () const {
    return Game_Data::getMaterial(getType()->material);
}

double Creature::getMoveForce () const {
    return getType()->moveForce;
}

double Creature::getMass () const {
    return getType()->mass;
}

double Creature::getMaximumSpeed () const {
    return getType()->maximumSpeed;
}

LightTemplate* Creature::getLightTemplate () const {
    string lightType = getType()->light;

    if (lightType.length() > 0) {
        return Game_Data::getLightTemplate(lightType);
    } else {
        return 0;
    }
}

string Creature::getCharacterColor () const {
    return getMaterial()->characterColor;
}

void Creature::stop () {
    velocity *= 0.0;
    force *= 0.0;
}

void Creature::brake () {
    Vector brake_force(getMoveForce() * 2.0, velocity.direction + 180.0);

    Math::clamp_angle(brake_force.direction);

    if (brake_force.magnitude / getMass() > velocity.magnitude) {
        brake_force.magnitude = velocity.magnitude * getMass();
    }

    force += brake_force;
}

Creature::Creature (const string& type, const Coords<double>& position) {
    this->type = type;
    this->position = position;
}

Collision_Rect<double> Creature::getBox () const {
    Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

    return Collision_Rect<double>(position.x, position.y, font->get_letter_width(), font->get_letter_height());
}

Coords<int32_t> Creature::getTilePosition () const {
    Collision_Rect<double> box = getBox();

    return Coords<int32_t>(box.x / box.w, box.y / box.h);
}

Collision_Rect<double> Creature::getCollisionBox () const {
    Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

    return Collision_Rect<double>(position.x + Game_Constants::CREATURE_COLLISION_REDUCTION,
                                  position.y + Game_Constants::CREATURE_COLLISION_REDUCTION,
                                  font->get_letter_width() - Game_Constants::CREATURE_COLLISION_REDUCTION * 2.0,
                                  font->get_letter_height() - Game_Constants::CREATURE_COLLISION_REDUCTION * 2.0);
}

const Vector& Creature::getVelocity () const {
    return velocity;
}

bool Creature::isAlive () const {
    return true;
}

LightTemplate* Creature::updateLightSource () {
    LightTemplate* lightTemplate = getLightTemplate();

    LightSource::updateLightSource(lightTemplate);

    return lightTemplate;
}

int32_t Creature::getLightRange () const {
    return LightSource::getLightRange(getLightTemplate());
}

bool Creature::isLit () const {
    return lightColor.getAlpha() > 0;
}

void Creature::applyLight () {
    lightColor.clear();

    const vector<vector<Tile>>& tiles = Game::getTiles();
    Coords<int32_t> tilePosition = getTilePosition();
    Coords<int32_t> worldDimensions = Game::getWorldDimensions();

    for (int32_t x = tilePosition.x;
         x < tilePosition.x + 1; x++) {
        for (int32_t y = tilePosition.y;
             y < tilePosition.y + 1; y++) {
            if (x >= 0 && y >= 0 && x < worldDimensions.x && y < worldDimensions.y) {
                if (tiles[x][y].isLit() && Collision::check_rect(tiles[x][y].getBox(Coords<int32_t>(x, y)),
                                                                 getCollisionBox())) {
                    double lightLevelFactor = (double) tiles[x][y].getLightColor().getAlpha() /
                                              (double) Game_Constants::MAXIMUM_LIGHT_LEVEL;

                    if (lightLevelFactor > Game_Constants::CREATURE_LIGHT_LEVEL_MAXIMUM) {
                        lightLevelFactor = Game_Constants::CREATURE_LIGHT_LEVEL_MAXIMUM;
                    }

                    if (!isLit()) {
                        lightColor.set(tiles[x][y].getLightColor().getRed() * lightLevelFactor,
                                       tiles[x][y].getLightColor().getGreen() * lightLevelFactor,
                                       tiles[x][y].getLightColor().getBlue() * lightLevelFactor,
                                       tiles[x][y].getLightColor().getAlpha());
                    } else {
                        lightColor.hdrAdd(tiles[x][y].getLightColor().getRed() * lightLevelFactor,
                                          tiles[x][y].getLightColor().getGreen() * lightLevelFactor,
                                          tiles[x][y].getLightColor().getBlue() * lightLevelFactor,
                                          tiles[x][y].getLightColor().getAlpha());
                    }
                }
            }
        }
    }
}

void Creature::setThrustAngle (const string& direction) {
    double angle = 0.0;

    if (direction != "none") {
        if (direction == "left") {
            angle = 180.0;
        } else if (direction == "right") {
            angle = 0.0;
        } else if (direction == "up") {
            angle = 90.0;
        } else if (direction == "down") {
            angle = 270.0;
        } else if (direction == "left_up") {
            angle = 135.0;
        } else if (direction == "right_up") {
            angle = 45.0;
        } else if (direction == "left_down") {
            angle = 225.0;
        } else if (direction == "right_down") {
            angle = 315.0;
        }

        force += Vector(getMoveForce(), angle);
    } else {
        brake();
    }
}

void Creature::accelerate () {
    if (isAlive()) {
        Vector acceleration = force / getMass();

        velocity += acceleration;

        if (velocity.magnitude > getMaximumSpeed()) {
            velocity.magnitude = getMaximumSpeed();
        } else if (velocity.magnitude < -getMaximumSpeed()) {
            velocity.magnitude = -getMaximumSpeed();
        }

        force *= 0.0;
    }
}

void Creature::movement () {
    if (isAlive()) {
        Vector_Components vc = velocity.get_components();
        double movementX = vc.a / Engine::UPDATE_RATE;

        for (int32_t i = 0; i < Game_Constants::CREATURE_COLLISION_STEPS; i++) {
            Coords<double> oldPosition = position;

            position.x += movementX / Game_Constants::CREATURE_COLLISION_STEPS;

            if (tileCollision(oldPosition)) {
                break;
            }
        }

        double movementY = vc.b / Engine::UPDATE_RATE;

        for (int32_t i = 0; i < Game_Constants::CREATURE_COLLISION_STEPS; i++) {
            Coords<double> oldPosition = position;

            position.y += movementY / Game_Constants::CREATURE_COLLISION_STEPS;

            if (tileCollision(oldPosition)) {
                break;
            }
        }

        if (position.x < 0.0) {
            position.x = 0.0;
            stop();
        }

        if (position.y < 0.0) {
            position.y = 0.0;
            stop();
        }

        Coords<double> worldDimensionsPixels = Game::getWorldDimensionsPixels();
        Collision_Rect<double> box = getCollisionBox();

        if (box.x + box.w >= worldDimensionsPixels.x) {
            position.x = worldDimensionsPixels.x - box.w;
            stop();
        }

        if (box.y + box.h >= worldDimensionsPixels.y) {
            position.y = worldDimensionsPixels.y - box.h;
            stop();
        }
    }
}

bool Creature::tileCollision (const Coords<double>& oldPosition) {
    const vector<vector<Tile>>& tiles = Game::getTiles();
    Coords<int32_t> tilePosition = getTilePosition();
    Coords<int32_t> worldDimensions = Game::getWorldDimensions();

    for (int32_t x = tilePosition.x - 1; x < tilePosition.x + 2; x++) {
        for (int32_t y = tilePosition.y - 1; y < tilePosition.y + 2; y++) {
            if (x >= 0 && y >= 0 && x < worldDimensions.x && y < worldDimensions.y) {
                Collision_Rect<double> tileBox = Tile::getBox(Coords<int32_t>(x, y));

                if (Collision::check_rect(getCollisionBox(), tileBox)) {
                    if (tiles[x][y].isSolid()) {
                        position = oldPosition;

                        stop();

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void Creature::render () const {
    Collision_Rect<double> box = getBox();

    if (Collision::check_rect(box * Game_Manager::camera_zoom, Game_Manager::camera)) {
        Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);
        Color finalCharacterColor = Lighting::applyLightToColor(getCharacterColor(), lightColor);

        font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                   box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1, getCharacter()),
                   &finalCharacterColor, 1.0, Game_Manager::camera_zoom, Game_Manager::camera_zoom);
    }
}
