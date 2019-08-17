#ifndef SDL_UTILS_UTILS
#define SDL_UTILS_UTILS

#ifdef SDL_UTILS_NO_STD_LIB

#include <SDL.h>

#define su_malloc(size) SDL_malloc(size)
#define su_realloc(ptr, size) SDL_realloc(ptr, size)
#define su_calloc(nelems, size) SDL_calloc(nelems, size)
#define su_free(ptr) SDL_free(ptr)

#define su_memmove(dst, src, size) SDL_memmove(dst, src, size)

#else

#include <stdlib.h>
#include <string.h>

#define su_malloc(size)            malloc(size)
#define su_realloc(ptr, size)      realloc(ptr, size)
#define su_calloc(nelems, size)    calloc(nelems, size)
#define su_free(ptr)               free(ptr)

#define su_memmove(dst, src, size) memmove(dst, src, size)

#endif

#endif