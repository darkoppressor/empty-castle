/* Copyright (c) 2012 Cheese and Bacon Games, LLC */
/* This file is licensed under the MIT License. */
/* See the file docs/LICENSE.txt for the full license text. */

#include "better_color.h"

#include <algorithm>

using namespace std;

BetterColor::BetterColor () {
    clear();
}

BetterColor::BetterColor (int16_t red, int16_t green, int16_t blue, int16_t alpha) {
    set(red, green, blue, alpha);
}

BetterColor::BetterColor (const BetterColor* color) {
    this->red = color->red;
    this->green = color->green;
    this->blue = color->blue;
    this->alpha = color->alpha;
}

void BetterColor::clear () {
    red = MINIMUM_CHANNEL_VALUE;
    green = MINIMUM_CHANNEL_VALUE;
    blue = MINIMUM_CHANNEL_VALUE;
    alpha = MINIMUM_CHANNEL_VALUE;
}

void BetterColor::set (int16_t red, int16_t green, int16_t blue, int16_t alpha) {
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

int16_t BetterColor::getRed () const {
    return red;
}

void BetterColor::setRed (int16_t red) {
    this->red = red;
}

int16_t BetterColor::getGreen () const {
    return green;
}

void BetterColor::setGreen (int16_t green) {
    this->green = green;
}

int16_t BetterColor::getBlue () const {
    return blue;
}

void BetterColor::setBlue (int16_t blue) {
    this->blue = blue;
}

int16_t BetterColor::getAlpha () const {
    return alpha;
}

void BetterColor::setAlpha (int16_t alpha) {
    this->alpha = alpha;
}

void BetterColor::hdrAdd (int16_t red, int16_t green, int16_t blue, int16_t alpha) {
    this->red += red;
    this->green += green;
    this->blue += blue;
    this->alpha += alpha;
}

BetterColor BetterColor::getHdrRescaled () const {
    BetterColor color(this);
    int16_t highestChannel = max(max(color.red, color.green), max(color.blue, color.alpha));

    if (highestChannel > MAXIMUM_CHANNEL_VALUE) {
        double scaleFactor = (double) MAXIMUM_CHANNEL_VALUE / (double) highestChannel;

        color.setRed(color.getRed() * scaleFactor);
        color.setGreen(color.getGreen() * scaleFactor);
        color.setBlue(color.getBlue() * scaleFactor);
        color.setAlpha(color.getAlpha() * scaleFactor);
    }

    return color;
}
