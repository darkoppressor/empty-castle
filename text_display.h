/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef text_display_h
#define text_display_h

#include <information.h>
#include <timer.h>

#include <cstdint>
#include <vector>
#include <string>

class TextDisplay {
    private:
        Information display;
        // Used to determine if a line should be shown
        std::vector<Timer> textTimers;

    public:
        void setup(std::int32_t parserHeight);

        void resetTextTimers();
        void restartTextTimers();
        void clear();
        void add(std::string line);

        void scroll(bool up);

        void handleInputStates();
        bool handleInputEvents();

        void animate();
        void render();
};

#endif
