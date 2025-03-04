/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */

#ifndef game_h
#define game_h

#include "tile.h"
#include "creature.h"
#include "text_parser.h"
#include "text_display.h"

#include <coords.h>
#include <collision.h>
#include <rng.h>

#include <cstdint>
#include <vector>
#include <string>

class Game {
    private:
        static RNG rng;
        // tiles
        static std::int32_t worldWidth;
        // tiles
        static std::int32_t worldHeight;
        static std::vector<MapCharacter> mapCharacters;
        static std::vector<std::vector<Tile>> tiles;
        // creatures[0] represets the player
        static std::vector<Creature> creatures;
        static TextParser textParser;
        static TextDisplay textDisplay;

    public:
        static RNG& getRng();
        // tile coordinates
        static Coords<std::int32_t> getWorldDimensions();
        // pixel coordinates
        static Coords<double> getWorldDimensionsPixels();
        static const MapCharacter& getMapCharacter(std::uint32_t type);

        static std::vector<std::vector<Tile>>& getTiles();

        static Creature& getPlayer();
        static bool isTextParserOn();
        static void updateTextParserFocus();
        static void toggleTextParser(bool commit);
        static void handleTextParserInputStates();
        static bool handleTextParserInputEvents();
        static void addDisplayText(const std::string& line);
        static void scrollTextDisplay(bool up);
        static void handleTextDisplayInputStates();
        static bool handleTextDisplayInputEvents();
        static void clear_world();
        static void generate_world();
        static void tick();
        static void ai();
        static void movement();
        static void events();
        static void animate();
        static void render();
        static void render_to_textures();
        static void update_background();
        static void render_background();
        // The returned collision rectangle's values are:
        // x => starting x tile (inclusive)
        // y => starting y tile (inclusive)
        // w => ending x tile (exclusive)
        // h => ending y tile (exclusive)
        static Collision_Rect<std::int32_t> getCameraTileBox(std::int32_t padding);
        static void playerThrust(const std::string& direction);
        static bool moveInputState(const std::string& direction);
};

#endif
