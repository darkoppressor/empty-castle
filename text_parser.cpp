/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "text_parser.h"
#include "game_constants.h"

#include <render.h>
#include <game_window.h>
#include <engine.h>
#include <object_manager.h>

#include <boost/algorithm/string.hpp>

using namespace std;

TextParser::TextParser () {
    on = false;
}

void TextParser::setup () {
    input.text_mutable = true;
    input.max_text_length = Game_Constants::MAXIMUM_TEXT_PARSER_LENGTH;
    input.allowed_input.push_back("backspace");
    input.allowed_input.push_back("letters");
    input.allowed_input.push_back("space");
    input.font = Game_Constants::TEXT_PARSER_FONT;
    input.background_type = "standard";
    input.background_opacity = 1.0;
    input.scroll_width = Game_Window::width() / Object_Manager::get_font(input.font)->spacing_x - 1;
    input.scroll_height = 1;
    input.set_dimensions();
    input.x = -1;
    input.y = Game_Window::height() - 5.0 - 16.0;
    input.start_x = input.x;
    input.start_y = input.y;
    input.center_in_window(Game_Window::width(), Game_Window::height());
}

bool TextParser::isOn () const {
    return on;
}

void TextParser::updateFocus () {
    if (on && !Engine::console.on) {
        input.begin_editing();
    }
}

void TextParser::toggle (bool commit) {
    on = !on;

    onChanged(commit);
}

void TextParser::set (bool state) {
    on = state;
}

void TextParser::onChanged (bool commit) {
    if (on) {
        input.begin_editing();
    } else {
        Engine::clear_mutable_info();

        if (commit) {
            commitText();
        }
    }
}

void TextParser::commitText () {
    string line = input.get_cursor_line();

    input.set_text("");

    boost::algorithm::trim(line);

    vector<string> words;
    boost::algorithm::split(words, line, boost::algorithm::is_any_of(" "));

    for (int32_t i = 0; i < words.size(); i++) {
        if (words[i].length() == 0) {
            words.erase(words.begin() + i);

            i--;
        }
    }

    ///QQQ handle commit
}

void TextParser::handleInputStates () {
    if (on) {
        int mouseX = 0;
        int mouseY = 0;

        Engine::get_mouse_state(&mouseX, &mouseY);

        input.handle_input_states(mouseX, mouseY, 0, 0);
    }
}

bool TextParser::handleInputEvents () {
    bool event_consumed = false;

    if (on && Engine::mouse_allowed()) {
        int mouseX = 0;
        int mouseY = 0;

        Engine::get_mouse_state(&mouseX, &mouseY);

        if (!event_consumed) {
            event_consumed = input.handle_input_events(mouseX, mouseY, 0, 0);
        }
    }

    return event_consumed;
}

void TextParser::animate () {
    if (on) {
        input.animate();
    }
}

void TextParser::render () {
    if (on) {
        input.render(0, 0);
    }
}
