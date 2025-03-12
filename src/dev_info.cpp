/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "game.h"

#include <engine.h>
#include <game_manager.h>
#include <font.h>
#include <object_manager.h>
#include <options.h>
#include <network_engine.h>
#include <render.h>
#include <engine_strings.h>

using namespace std;

void Engine::render_dev_info () {
    string msg = "";

    if (Game_Manager::in_progress) {
        msg += "Camera Position: " + Strings::num_to_string(Game_Manager::camera.x) + "," +
               Strings::num_to_string(Game_Manager::camera.y) + "\n";
        msg += "Camera Dimenions: " + Strings::num_to_string(Game_Manager::camera.w / Game_Manager::camera_zoom) + "," +
               Strings::num_to_string(Game_Manager::camera.h / Game_Manager::camera_zoom) + "\n";
        msg += "Camera Zoom: " + Strings::num_to_string(Game_Manager::camera_zoom) + "\n";

        msg += "\nPlayer Position: " + Strings::num_to_string(Game::getPlayer().getBox().x) + ", " +
               Strings::num_to_string(Game::getPlayer().getBox().y) + "\n";
        msg += "Player Tile Position: " + Strings::num_to_string(Game::getPlayer().getTilePosition().x) + ", " +
               Strings::num_to_string(Game::getPlayer().getTilePosition().y) + "\n";
        msg += "Player Dimensions: " + Strings::num_to_string(Game::getPlayer().getBox().w) + ", " +
               Strings::num_to_string(Game::getPlayer().getBox().h) + "\n";
        msg += "Player Velocity: " + Strings::num_to_string(Game::getPlayer().getVelocity().magnitude) + " m/s, " +
               Strings::num_to_string(Game::getPlayer().getVelocity().direction) + string(1, 167) + "\n";
    }

    if (msg.length() > 0) {
        Bitmap_Font* font = Object_Manager::get_font("small");
        double y = 2.0;

        if (Options::fps) {
            y += font->spacing_y;

            if (Network_Engine::status != "off") {
                y += font->spacing_y * 2.0;
            }
        }

        Render::render_rectangle(2.0, y, Strings::longest_line(msg) * font->spacing_x,
                                 Strings::newline_count(msg) * font->spacing_y, 0.75, "ui_black");
        font->show(2.0, y, msg, "red");
    }
}
