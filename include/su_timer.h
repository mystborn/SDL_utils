#ifndef SDL_UTILS_TIMER_H
#define SDL_UTILS_TIMER_H

#include <SDL.h>
#include "su_utils.h"

typedef struct TimerUtil {
    Uint32 start_ticks;
    Uint32 paused_ticks;
    SDL_bool paused;
    SDL_bool started;
} TimerUtil;

static inline void timer_init(TimerUtil*);
static inline TimerUtil* timer_create(void);
static inline void timer_free(TimerUtil* timer);
static inline void timer_start(TimerUtil* timer);
static inline void timer_stop(TimerUtil* timer);
static inline void timer_pause(TimerUtil* timer);
static inline void timer_resume(TimerUtil* timer);
static inline Uint32 timer_ticks(TimerUtil* timer);
static inline SDL_bool timer_started(TimerUtil* timer);
static inline SDL_bool timer_paused(TimerUtil* timer);

static inline void timer_init(TimerUtil* timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->paused = SDL_FALSE;
    timer->started = SDL_FALSE;
}

static inline TimerUtil* timer_create(void) {
    TimerUtil* timer = su_malloc(sizeof(*timer));
    if(timer == NULL)
        return NULL;
    timer_init(timer);
    return timer;
}

static inline void timer_free(TimerUtil* timer) {
    su_free(timer);
}

static inline void timer_start(TimerUtil* timer) {
    timer->started = SDL_TRUE;
    timer->paused = SDL_FALSE;
    timer->paused_ticks = 0;
    timer->start_ticks = SDL_GetTicks();
}

static inline void timer_stop(TimerUtil* timer) {
    timer->start_ticks = 0;
    timer->paused_ticks = 0;
    timer->paused = SDL_FALSE;
    timer->started = SDL_FALSE;
}

static inline void timer_pause(TimerUtil* timer) {
    if (timer->started && !timer->paused) {
        timer->paused_ticks = SDL_GetTicks() - timer->start_ticks;
        timer->paused = SDL_TRUE;
        timer->start_ticks = 0;
    }
}

static inline void timer_resume(TimerUtil* timer) {
    if (timer->started && timer->paused) {
        timer->paused = SDL_FALSE;
        timer->start_ticks = SDL_GetTicks() - timer->paused_ticks;
        timer->paused_ticks = 0;
    }
}

static inline Uint32 timer_ticks(TimerUtil* timer) {
    Uint32 time = 0;
    if (timer->started) {
        if (timer->paused)
            time = timer->paused_ticks;
        else
            time = SDL_GetTicks() - timer->start_ticks;
    }

    return time;
}

static inline SDL_bool timer_started(TimerUtil* timer) {
    return timer->started;
}

static inline SDL_bool timer_paused(TimerUtil* timer) {
    return timer->paused;
}

#endif