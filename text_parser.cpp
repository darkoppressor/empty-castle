/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "text_parser.h"

#include <render.h>
#include <game_window.h>

using namespace std;

TextParser::TextParser () {
    on = false;
}

void TextParser::toggle (bool commit) {
    on = !on;

    if (!on && commit) {
        commitText();
    }
}

void TextParser::set (bool state, bool commit) {
    on = state;

    if (!on && commit) {
        commitText();
    }
}

void TextParser::commitText () {
    ///QQQ handle commit
}

void TextParser::render () const {
    if (on) {
        const double borderThickness = 2.0;
        double x = 5.0;
        double y = Game_Window::height() - 5.0 - 16.0;
        double w = Game_Window::width() - 5.0 * 2.0;
        double h = 16.0;

        Render::render_rectangle_empty(x - borderThickness, y - borderThickness, w + borderThickness * 2.0,
                                       h + borderThickness * 2.0, 0.75, "ui_white", borderThickness);
        Render::render_rectangle(x, y, w, h, 0.75, "ui_black");
    }
}
