#ifndef SDL_UTILS_DATA_TYPES_H
#define SDL_UTILS_DATA_TYPES_H

/**
    \file This file defines some general purpose data structures
          and renames some of the built in SDL ones to have more
          sensible names, in my opinion.
*/

#include <SDL.h>

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef SDL_Point Point;
typedef SDL_Rect Rectangle;
typedef SDL_Texture Texture;

#endif //SKY_DATA_TYPES_H