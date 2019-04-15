/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#ifndef text_parser_h
#define text_parser_h

class TextParser {
    private:
        bool on;

    public:
        TextParser ();

        void toggle(bool commit);
        void set(bool state, bool commit);

        void commitText();

        void render() const;
};

#endif
