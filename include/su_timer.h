#ifndef SDL_UTILS_TIMER_H
#define SDL_UTILS_TIMER_H

#include <SDL.h>
#include "su_utils.h"

/**
    Defines a simple timer.

    \remark Based off of the code from this tutorial:
            http://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php
*/
typedef struct TimerUtil {
    Uint32 start_ticks;
    Uint32 paused_ticks;
    SDL_bool paused;
    SDL_bool started;
} TimerUtil;

/**
    Initializes a timer.
*/
static inline void timer_init(TimerUtil*);

/**
    Allocates and initializes a new timer.
*/
static inline TimerUtil* timer_create(void);

/**
    Frees any resources used by the timer, then frees the timer itself.
    Only use if the timer was allocated with timer_create.
*/
static inline void timer_free(TimerUtil* timer);

/**
    Starts the timer.
*/
static inline void timer_start(TimerUtil* timer);

/**
    Stops the timer, in effect resetting it. Only do this if you want to
    start a fresh calculation.
*/
static inline void timer_stop(TimerUtil* timer);

/**
    Pauses the timer.
*/
static inline void timer_pause(TimerUtil* timer);

/**
    Resumes the timer if it had been paused.
*/
static inline void timer_resume(TimerUtil* timer);

/**
    Gets the number of milliseconds since the timer had been started.
*/
static inline Uint32 timer_ticks(TimerUtil* timer);

/**
    Determines if the timer has been started.
*/
static inline SDL_bool timer_started(TimerUtil* timer);

/**
    Determines if the timer is currently paused.
*/
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