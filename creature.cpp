/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "creature.h"
#include "game_constants.h"
#include "game_data.h"
#include "game.h"

#include <font.h>
#include <object_manager.h>
#include <game_manager.h>
#include <engine.h>
#include <int_math.h>

using namespace std;

CreatureTemplate* Creature::getType () const {
    return Game_Data::getCreatureTemplate(type);
}

unsigned char Creature::getCharacter () const {
    return getType()->character;
}

string Creature::getCharacterColor () const {
    return getType()->characterColor;
}

int32_t Creature::getMoveForce () const {
    return getType()->moveForce;
}

int32_t Creature::getMass () const {
    return getType()->mass;
}

int32_t Creature::getMaximumSpeed () const {
    return getType()->maximumSpeed;
}

Creature::Creature (const string& type, const Coords<int32_t>& position) {
    this->type = type;
    this->position = position;
}

Collision_Rect<int32_t> Creature::getBox () const {
    Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

    return Collision_Rect<int32_t>(position.x, position.y,
                                   (int32_t) font->get_letter_width(), (int32_t) font->get_letter_height());
}

Coords<uint32_t> Creature::getTilePosition () const {
    Collision_Rect<int32_t> box = getBox();

    return Coords<uint32_t>((uint32_t) box.x / (uint32_t) box.w, (uint32_t) box.y / (uint32_t) box.h);
}

Collision_Rect<int32_t> Creature::getCollisionBox () const {
    Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

    return Collision_Rect<int32_t>(position.x + Game_Constants::CREATURE_COLLISION_REDUCTION,
                                   position.y + Game_Constants::CREATURE_COLLISION_REDUCTION,
                                   (int32_t) font->get_letter_width() - Game_Constants::CREATURE_COLLISION_REDUCTION* 2,
                                   (int32_t) font->get_letter_height() -
                                   Game_Constants::CREATURE_COLLISION_REDUCTION* 2);
}

bool Creature::isAlive () const {
    return true;
}

void Creature::setThrustAngle (const string& direction) {
    int32_t angle = 0;

    if (direction != "none") {
        if (direction == "left") {
            angle = 180;
        } else if (direction == "right") {
            angle = 0;
        } else if (direction == "up") {
            angle = 90;
        } else if (direction == "down") {
            angle = 270;
        } else if (direction == "left_up") {
            angle = 135;
        } else if (direction == "right_up") {
            angle = 45;
        } else if (direction == "left_down") {
            angle = 225;
        } else if (direction == "right_down") {
            angle = 315;
        }

        force += Int_Vector(getMoveForce(), angle);
    } else {
        brake();
    }
}

void Creature::brake () {
    Int_Vector brake_force(getMoveForce() * 2, velocity.direction + 180);

    Int_Math::clamp_angle(brake_force.direction);

    if (brake_force.magnitude / getMass() > velocity.magnitude) {
        brake_force.magnitude = velocity.magnitude * getMass();
    }

    force += brake_force;
}

void Creature::accelerate () {
    if (isAlive()) {
        Int_Vector acceleration = force / getMass();

        velocity += acceleration;

        if (velocity.magnitude > getMaximumSpeed()) {
            velocity.magnitude = getMaximumSpeed();
        } else if (velocity.magnitude < -getMaximumSpeed()) {
            velocity.magnitude = -getMaximumSpeed();
        }

        force *= 0;
    }
}

void Creature::movement () {
    if (isAlive()) {
        Int_Vector_Components vc = velocity.get_components();
        int32_t movementX = vc.a / (int32_t) Engine::UPDATE_RATE;

        for (int32_t i = 0; i < Game_Constants::CREATURE_COLLISION_STEPS; i++) {
            Coords<int32_t> oldPosition = position;
            position.x += movementX / Game_Constants::CREATURE_COLLISION_STEPS;

            if (tileCollision(oldPosition)) {
                break;
            }
        }

        int32_t movementY = vc.b / (int32_t) Engine::UPDATE_RATE;

        for (int32_t i = 0; i < Game_Constants::CREATURE_COLLISION_STEPS; i++) {
            Coords<int32_t> oldPosition = position;
            position.y += movementY / Game_Constants::CREATURE_COLLISION_STEPS;

            if (tileCollision(oldPosition)) {
                break;
            }
        }

        if (position.x < 0) {
            position.x = 0;
        }

        if (position.y < 0) {
            position.y = 0;
        }

        Coords<int32_t> worldDimensionsPixels = Game::getWorldDimensionsPixels();
        Collision_Rect<int32_t> box = getCollisionBox();

        if (box.x + box.w >= worldDimensionsPixels.x) {
            position.x = worldDimensionsPixels.x - box.w;
            force *= 0;
        }

        if (box.y + box.h >= worldDimensionsPixels.y) {
            position.y = worldDimensionsPixels.y - box.h;
            force *= 0;
        }
    }
}

bool Creature::tileCollision (const Coords<int32_t>& oldPosition) {
    const vector<vector<Tile>>& tiles = Game::getTiles();
    Coords<uint32_t> tilePosition = getTilePosition();
    Coords<uint32_t> worldDimensions = Game::getWorldDimensions();

    for (int32_t x = (int32_t) tilePosition.x - 1; x < (int32_t) tilePosition.x + 2; x++) {
        for (int32_t y = (int32_t) tilePosition.y - 1; y < (int32_t) tilePosition.y + 2; y++) {
            if (x >= 0 && y >= 0 && x < (int32_t) worldDimensions.x && y < (int32_t) worldDimensions.y) {
                Collision_Rect<int32_t> tileBox = Tile::getBox(Coords<uint32_t>(x, y));

                if (Collision::check_rect(getCollisionBox(), tileBox)) {
                    if (tiles[x][y].isSolid()) {
                        position = oldPosition;

                        force *= 0;

                        return true;
                    }
                }
            }
        }
    }

    return false;
}

void Creature::render () const {
    Collision_Rect<int32_t> box = getBox();
    Collision_Rect<double> boxRender(box.x, box.y, box.w, box.h);

    if (Collision::check_rect(boxRender * Game_Manager::camera_zoom, Game_Manager::camera)) {
        Bitmap_Font* font = Object_Manager::get_font(Game_Constants::DISPLAY_FONT);

        font->show(box.x * Game_Manager::camera_zoom - Game_Manager::camera.x,
                   box.y * Game_Manager::camera_zoom - Game_Manager::camera.y, string(1,
                                                                                      getCharacter()),
                   getCharacterColor(), 1.0, Game_Manager::camera_zoom, Game_Manager::camera_zoom);
    }
}