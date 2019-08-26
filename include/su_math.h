#ifndef SDL_UTILS_MATH_H
#define SDL_UTILS_MATH_H

static inline int fast_floor(float x) {
    return (int)(x + 32768.0f) - 32768;
}

static inline int fast_ceil(float x) {
    return 32768 - (int)(32768.f - x);
}

#endif