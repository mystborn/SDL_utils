#ifndef SDL_UTILS_MATH_H
#define SDL_UTILS_MATH_H

#include <math.h>

static inline int fast_floor(float x) {
    return (int)(x + 32768.0f) - 32768;
}

static inline int fast_ceil(float x) {
    return 32768 - (int)(32768.f - x);
}

static inline float floor_ext(float value, float n) {
    return floorf(value / n) * n;
}

static inline float ceil_ext(float value, float n) {
    return ceilf(value / n) * n;
}

static inline float round_ext(float value, float n) {
    return roundf(value / n) * n;
}

#endif