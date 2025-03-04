/* Copyright (c) Cheese and Bacon Games, LLC. See docs/LICENSE.md for details. */
/* This file incorporates code from libtcod. See the file docs/third-party-licenses/libtcod.txt. */

#include "field_of_view_source.h"

using namespace std;

FieldOfViewSource::FieldOfViewSource (const Coords<int32_t>& sourcePosition, const string& lightColor,
                                      uint32_t lightSourceId, int32_t maximumRadius) {
    this->sourcePosition = sourcePosition;
    this->lightColor = lightColor;
    this->lightSourceId = lightSourceId;
    this->maximumRadius = maximumRadius;
}

Coords<int32_t> FieldOfViewSource::getSourcePosition () const {
    return sourcePosition;
}

string FieldOfViewSource::getLightColor () const {
    return lightColor;
}

uint32_t FieldOfViewSource::getLightSourceId () const {
    return lightSourceId;
}

int32_t FieldOfViewSource::getMaximumRadius () const {
    return maximumRadius;
}
