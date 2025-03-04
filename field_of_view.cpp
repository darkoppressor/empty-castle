/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */
/* This file incorporates code from libtcod. See the file docs/thirdPartyLicenses/libtcod.txt. */

#include "field_of_view.h"
#include "game_constants.h"

#include "libtcod/bresenham.h"

using namespace std;

int32_t FieldOfView::maximum (int32_t a, int32_t b) {
    return a > b ? a : b;
}

int32_t FieldOfView::minimum (int32_t a, int32_t b) {
    return a < b ? a : b;
}

int16_t FieldOfView::getLightLevel (int32_t radius, int32_t maximumRadius) {
    return Game_Constants::MAXIMUM_LIGHT_LEVEL -
           (int16_t) ((double) radius / (double) maximumRadius * (double) Game_Constants::MAXIMUM_LIGHT_LEVEL);
}

void FieldOfView::castRay (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles,
                           const FieldOfViewSource& source, int32_t xo, int32_t yo, int32_t xd, int32_t yd, int32_t r2,
                           bool lightWalls) {
    int32_t curx = xo;
    int32_t cury = yo;
    bool in = false;
    bool blocked = false;
    bool end = false;
    TCOD_bresenham_data_t bresenham_data;

    TCOD_line_init_mt(xo, yo, xd, yd, &bresenham_data);

    int32_t offset = curx + cury * worldWidth;
    int32_t tileCount = worldWidth * worldHeight;

    if (0 <= offset && offset < tileCount) {
        in = true;
        tiles[curx][cury].applyLight(source.getLightSourceId(), Game_Constants::MAXIMUM_LIGHT_LEVEL,
                                     source.getLightColor());
        tiles[curx][cury].setExplored(true);
    }

    while (!end) {
        // Reached xd, yd
        end = TCOD_line_step_mt(&curx, &cury, &bresenham_data);
        offset = curx + cury * worldWidth;

        // Check radius
        int32_t cur_radius = (curx - xo) * (curx - xo) + (cury - yo) * (cury - yo);

        if (r2 > 0) {
            if (cur_radius > r2) {
                return;
            }
        }

        if (0 <= offset && offset < tileCount) {
            in = true;

            if (!blocked && tiles[curx][cury].isOpaque()) {
                blocked = true;
            } else if (blocked) {
                // Wall
                return;
            }

            if (lightWalls || !blocked) {
                tiles[curx][cury].applyLight(source.getLightSourceId(), getLightLevel(cur_radius, r2),
                                             source.getLightColor());
                tiles[curx][cury].setExplored(true);
            }
        } else if (in) {
            // Ray out of map
            return;
        }
    }
}

void FieldOfView::postProcess (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles,
                               const FieldOfViewSource& source, int32_t r2, int32_t x0, int32_t y0, int32_t x1,
                               int32_t y1, int32_t dx, int32_t dy) {
    for (int32_t cx = x0; cx <= x1; cx++) {
        for (int32_t cy = y0; cy <= y1; cy++) {
            int32_t x2 = cx + dx;
            int32_t y2 = cy + dy;
            uint32_t offset = cx + cy * worldWidth;
            int32_t tileCount = worldWidth * worldHeight;

            if (offset < (uint32_t) (tileCount) && tiles[cx][cy].isLit() && !tiles[cx][cy].isOpaque()) {
                int32_t cur_radius = (cx - source.getSourcePosition().x) * (cx - source.getSourcePosition().x) +
                                     (cy - source.getSourcePosition().y) * (cy - source.getSourcePosition().y);

                if (x2 >= x0 && x2 <= x1) {
                    uint32_t offset2 = x2 + cy * worldWidth;

                    if (offset2 < (uint32_t) (tileCount) && tiles[x2][cy].isOpaque()) {
                        tiles[x2][cy].applyLight(source.getLightSourceId(), getLightLevel(cur_radius, r2),
                                                 source.getLightColor());
                        tiles[x2][cy].setExplored(true);
                    }
                }

                if (y2 >= y0 && y2 <= y1) {
                    uint32_t offset2 = cx + y2 * worldWidth;

                    if (offset2 < (uint32_t) (tileCount) && tiles[cx][y2].isOpaque()) {
                        tiles[cx][y2].applyLight(source.getLightSourceId(), getLightLevel(cur_radius, r2),
                                                 source.getLightColor());
                        tiles[cx][y2].setExplored(true);
                    }
                }

                if (x2 >= x0 && x2 <= x1 && y2 >= y0 && y2 <= y1) {
                    uint32_t offset2 = x2 + y2 * worldWidth;

                    if (offset2 < (uint32_t) (tileCount) && tiles[x2][y2].isOpaque()) {
                        tiles[x2][y2].applyLight(source.getLightSourceId(), getLightLevel(cur_radius, r2),
                                                 source.getLightColor());
                        tiles[x2][y2].setExplored(true);
                    }
                }
            }
        }
    }
}

void FieldOfView::prepareToComputeFov (const Collision_Rect<int32_t>& cameraTileBox, int32_t worldWidth,
                                       int32_t worldHeight, vector<vector<Tile>>& tiles) {
    for (int32_t x = cameraTileBox.x; x < cameraTileBox.w; x++) {
        for (int32_t y = cameraTileBox.y; y < cameraTileBox.h; y++) {
            if (x >= 0 && y >= 0 && x < worldWidth && y < worldHeight) {
                tiles[x][y].clearLightColor();
            }
        }
    }
}

void FieldOfView::computeFov (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles,
                              const FieldOfViewSource& source, bool lightWalls) {
    // Circular ray casting
    int32_t xmin = 0;
    int32_t ymin = 0;
    int32_t xmax = worldWidth;
    int32_t ymax = worldHeight;
    int32_t r2 = source.getMaximumRadius() * source.getMaximumRadius();

    if (source.getMaximumRadius() > 0) {
        xmin = maximum(0, source.getSourcePosition().x - source.getMaximumRadius());
        ymin = maximum(0, source.getSourcePosition().y - source.getMaximumRadius());
        xmax = minimum(worldWidth, source.getSourcePosition().x + source.getMaximumRadius() + 1);
        ymax = minimum(worldHeight, source.getSourcePosition().y + source.getMaximumRadius() + 1);
    }

    int32_t xo = xmin;
    int32_t yo = ymin;

    while (xo < xmax) {
        castRay(worldWidth, worldHeight, tiles, source, source.getSourcePosition().x, source.getSourcePosition().y,
                xo++, yo, r2, lightWalls);
    }

    xo = xmax - 1;
    yo = ymin + 1;

    while (yo < ymax) {
        castRay(worldWidth, worldHeight, tiles, source, source.getSourcePosition().x, source.getSourcePosition().y, xo,
                yo++, r2, lightWalls);
    }

    xo = xmax - 2;
    yo = ymax - 1;

    while (xo >= 0) {
        castRay(worldWidth, worldHeight, tiles, source, source.getSourcePosition().x, source.getSourcePosition().y,
                xo--, yo, r2, lightWalls);
    }

    xo = xmin;
    yo = ymax - 2;

    while (yo > 0) {
        castRay(worldWidth, worldHeight, tiles, source, source.getSourcePosition().x, source.getSourcePosition().y, xo,
                yo--, r2, lightWalls);
    }

    if (lightWalls) {
        // Post-processing artifact fix
        postProcess(worldWidth, worldHeight, tiles, source, r2, xmin, ymin, source.getSourcePosition().x,
                    source.getSourcePosition().y, -1, -1);
        postProcess(worldWidth, worldHeight, tiles, source, r2, source.getSourcePosition().x, ymin, xmax - 1,
                    source.getSourcePosition().y, 1, -1);
        postProcess(worldWidth, worldHeight, tiles, source, r2, xmin, source.getSourcePosition().y,
                    source.getSourcePosition().x, ymax - 1, -1, 1);
        postProcess(worldWidth, worldHeight, tiles, source, r2, source.getSourcePosition().x,
                    source.getSourcePosition().y, xmax - 1, ymax - 1, 1, 1);
    }
}
