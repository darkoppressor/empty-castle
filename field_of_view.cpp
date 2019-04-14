/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */
/* This file incorporates code from libtcod. See the file docs/third-party-licenses/libtcod.txt. */

#include "field_of_view.h"

#include "libtcod/bresenham.h"

using namespace std;

int32_t FieldOfView::maximum (int32_t a, int32_t b) {
    return a > b ? a : b;
}

int32_t FieldOfView::minimum (int32_t a, int32_t b) {
    return a < b ? a : b;
}

void FieldOfView::castRay (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles, int32_t xo, int32_t yo,
                           int32_t xd, int32_t yd, int32_t r2, bool lightWalls) {
    int32_t curx = xo;
    int32_t cury = yo;
    bool in = false;
    bool blocked = false;
    bool end = false;
    TCOD_bresenham_data_t bresenham_data;

    TCOD_line_init_mt(xo, yo, xd, yd, &bresenham_data);
    int32_t offset = curx + cury * worldWidth;

    if (0 <= offset && offset < worldWidth * worldHeight) {
        in = true;
        tiles[curx][cury].setSeen(true);
        tiles[curx][cury].setExplored(true);
    }

    while (!end) {
        // Reached xd, yd
        end = TCOD_line_step_mt(&curx, &cury, &bresenham_data);
        offset = curx + cury * worldWidth;

        if (r2 > 0) {
            // Check radius
            int32_t cur_radius = (curx - xo) * (curx - xo) + (cury - yo) * (cury - yo);

            if (cur_radius > r2) {
                return;
            }
        }

        if (0 <= offset && offset < worldWidth * worldHeight) {
            in = true;

            if (!blocked && tiles[curx][cury].isOpaque()) {
                blocked = true;
            } else if (blocked) {

                // Wall
                return;
            }

            if (lightWalls || !blocked) {
                tiles[curx][cury].setSeen(true);
                tiles[curx][cury].setExplored(true);
            }
        } else if (in) {

            // Ray out of map
            return;
        }
    }
}

void FieldOfView::postProcess (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles, int32_t x0,
                               int32_t y0, int32_t x1, int32_t y1, int32_t dx, int32_t dy) {
    for (int32_t cx = x0; cx <= x1; cx++) {
        for (int32_t cy = y0; cy <= y1; cy++) {
            int32_t x2 = cx + dx;
            int32_t y2 = cy + dy;
            uint32_t offset = cx + cy * worldWidth;

            if (offset < (uint32_t) (worldWidth * worldHeight) && tiles[cx][cy].isSeen() && !tiles[cx][cy].isOpaque()) {
                if (x2 >= x0 && x2 <= x1) {
                    uint32_t offset2 = x2 + cy * worldWidth;

                    if (offset2 < (uint32_t) (worldWidth * worldHeight) && tiles[x2][cy].isOpaque()) {
                        tiles[x2][cy].setSeen(true);
                        tiles[x2][cy].setExplored(true);
                    }
                }

                if (y2 >= y0 && y2 <= y1) {
                    uint32_t offset2 = cx + y2 * worldWidth;

                    if (offset2 < (uint32_t) (worldWidth * worldHeight) && tiles[cx][y2].isOpaque()) {
                        tiles[cx][y2].setSeen(true);
                        tiles[cx][y2].setExplored(true);
                    }
                }

                if (x2 >= x0 && x2 <= x1 && y2 >= y0 && y2 <= y1) {
                    uint32_t offset2 = x2 + y2 * worldWidth;

                    if (offset2 < (uint32_t) (worldWidth * worldHeight) && tiles[x2][y2].isOpaque()) {
                        tiles[x2][y2].setSeen(true);
                        tiles[x2][y2].setExplored(true);
                    }
                }
            }
        }
    }
}

void FieldOfView::prepareToComputeFov (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles) {
    for (int32_t x = 0; x < worldWidth; x++) {
        for (int32_t y = 0; y < worldHeight; y++) {
            tiles[x][y].setSeen(false);
        }
    }
}

void FieldOfView::computeFov (int32_t worldWidth, int32_t worldHeight, vector<vector<Tile>>& tiles,
                              const Coords<int32_t>& sourcePosition, int32_t maxRadius, bool lightWalls) {
    // Circular ray casting
    int32_t xmin = 0;
    int32_t ymin = 0;
    int32_t xmax = worldWidth;
    int32_t ymax = worldHeight;
    int32_t r2 = maxRadius * maxRadius;

    if (maxRadius > 0) {
        xmin = maximum(0, sourcePosition.x - maxRadius);
        ymin = maximum(0, sourcePosition.y - maxRadius);
        xmax = minimum(worldWidth, sourcePosition.x + maxRadius + 1);
        ymax = minimum(worldHeight, sourcePosition.y + maxRadius + 1);
    }

    int32_t xo = xmin;
    int32_t yo = ymin;

    while (xo < xmax) {
        castRay(worldWidth, worldHeight, tiles, sourcePosition.x, sourcePosition.y, xo++, yo, r2, lightWalls);
    }

    xo = xmax - 1;
    yo = ymin + 1;

    while (yo < ymax) {
        castRay(worldWidth, worldHeight, tiles, sourcePosition.x, sourcePosition.y, xo, yo++, r2, lightWalls);
    }

    xo = xmax - 2;
    yo = ymax - 1;

    while (xo >= 0) {
        castRay(worldWidth, worldHeight, tiles, sourcePosition.x, sourcePosition.y, xo--, yo, r2, lightWalls);
    }

    xo = xmin;
    yo = ymax - 2;

    while (yo > 0) {
        castRay(worldWidth, worldHeight, tiles, sourcePosition.x, sourcePosition.y, xo, yo--, r2, lightWalls);
    }

    if (lightWalls) {
        // Post-processing artifact fix
        postProcess(worldWidth, worldHeight, tiles, xmin, ymin, sourcePosition.x, sourcePosition.y, -1, -1);
        postProcess(worldWidth, worldHeight, tiles, sourcePosition.x, ymin, xmax - 1, sourcePosition.y, 1, -1);
        postProcess(worldWidth, worldHeight, tiles, xmin, sourcePosition.y, sourcePosition.x, ymax - 1, -1, 1);
        postProcess(worldWidth, worldHeight, tiles, sourcePosition.x, sourcePosition.y, xmax - 1, ymax - 1, 1, 1);
    }
}
