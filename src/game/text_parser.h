/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef text_parser_h
#define text_parser_h

#include <ui/information.h>

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
