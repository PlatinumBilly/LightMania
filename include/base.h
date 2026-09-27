#ifndef BASE_H
#define BASE_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

#define __TRY(expr)                                                            \
    do {                                                                       \
        if (!expr) {                                                           \
            SDL_Log("SDL Error at %s: %d :%s\n", __FILE__, __LINE__,           \
                    SDL_GetError());                                           \
            goto cleanup;                                                      \
        }                                                                      \
    } while (0)

#endif
