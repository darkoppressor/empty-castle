/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef text_parser_h
#define text_parser_h

#include <information.h>

#include <cstdint>

class TextParser {
    private:
        bool on;
        Information input;

    public:
        TextParser ();

        void setup();

        bool isOn() const;
        std::int32_t getHeight() const;

        void updateFocus();
        void toggle(bool commit);
        void set(bool state);
        void onChanged(bool commit);

        void commitText();

        void handleInputStates();
        bool handleInputEvents();

        void animate();
        void render();
};

#endif
