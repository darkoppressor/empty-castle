/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

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
