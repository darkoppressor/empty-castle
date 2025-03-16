/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#include "text_display.h"
#include "game_constants.h"

#include <strings/engine_strings.h>
#include <game_window.h>
#include <engine.h>
#include <data/object_manager.h>

using namespace std;

void TextDisplay::setup (int32_t parserHeight) {
    display.font = Game_Constants::TEXT_DISPLAY_FONT;
    display.background_type = "none";
    display.scrolling = true;
    display.scroll_width = Game_Window::width() / Object_Manager::get_font(display.font)->spacing_x - 1;
    display.scroll_height = Game_Constants::TEXT_DISPLAY_HEIGHT;
    display.set_dimensions();
    display.x = -1;
    display.y = Game_Window::height() - display.h - parserHeight;
    display.start_x = display.x;
    display.start_y = display.y;
    display.center_in_window(Game_Window::width(), Game_Window::height());

    resetTextTimers();
}

void TextDisplay::resetTextTimers () {
    textTimers.clear();

    for (size_t i = 0; i < Strings::newline_count(display.text) + 1; i++) {
        textTimers.push_back(Timer());
    }
}

void TextDisplay::restartTextTimers () {
    for (auto& timer : textTimers) {
        timer.start();
    }
}

void TextDisplay::clear () {
    display.text = "";

    resetTextTimers();
}

void TextDisplay::add (string line) {
    // The number of characters to search back in a line for a space when inserting a newline
    int32_t spaceSearchDistance = 6;

    // If the text extends beyond the text box, wrap it around
    for (int32_t i = 0, j = 0; i < line.length(); i++) {
        if (line[i] == '\n') {
            j = 0;
        } else if (j >= display.scroll_width) {
            j = 0;

            for (int32_t k = i; k >= 0; k--) {
                if (line[k] == ' ') {
                    line.erase(line.begin() + k);

                    line.insert(k, "\n");

                    i = k;

                    break;
                } else if (k == 0 || line[k] == '\n' || k < i - spaceSearchDistance) {
                    line.insert(i, "\n");

                    i--;

                    break;
                }
            }
        } else {
            j++;
        }
    }

    display.text += "\n" + line;

    while (Strings::newline_count(display.text) + 1 > Game_Constants::MAXIMUM_TEXT_DISPLAY_LINES) {
        display.text = Strings::erase_first_line(display.text);
    }

    display.scroll_offset = -Strings::newline_count(display.text);
    display.scroll_offset += display.scroll_height - 1;

    for (size_t i = 0; i < Strings::newline_count(line) + 1; i++) {
        // Create a timer for this line
        textTimers.push_back(Timer());

        // Start this line's timer
        textTimers.back().start();
    }

    while (textTimers.size() > Game_Constants::MAXIMUM_TEXT_DISPLAY_LINES) {
        // Forget the oldest chat line's timer
        textTimers.erase(textTimers.begin());
    }
}

void TextDisplay::scroll (bool up) {
    if (up) {
        display.scroll_up(0);
    } else {
        display.scroll_down(0);
    }

    restartTextTimers();
}

void TextDisplay::handleInputStates () {
    int mouseX = 0;
    int mouseY = 0;

    Engine::get_mouse_state(&mouseX, &mouseY);

    display.handle_input_states(mouseX, mouseY, 0, 0);
}

bool TextDisplay::handleInputEvents () {
    bool event_consumed = false;

    if (Engine::mouse_allowed()) {
        int mouseX = 0;
        int mouseY = 0;

        Engine::get_mouse_state(&mouseX, &mouseY);

        if (!event_consumed) {
            event_consumed = display.handle_input_events(mouseX, mouseY, 0, 0);
        }
    }

    return event_consumed;
}

void TextDisplay::animate () {
    display.animate();
}

void TextDisplay::render () {
    string text = display.text;

    for (int32_t i = 0, line = 0; i < display.text.length(); i++) {
        if (Strings::is_newline_character(display.text[i])) {
            line++;
        } else {
            if (!textTimers[line].is_started() ||
                (textTimers[line].is_started() &&
                 textTimers[line].get_ticks() >= Game_Constants::TEXT_DISPLAY_TIMEOUT)) {
                display.text.erase(display.text.begin() + i);
                i--;
            }
        }
    }

    display.render(0, 0);

    display.text = text;
}
