#include "include/GameEngine.h"
#include "include/base.h"

#define _TRY(expr)                                                             \
    do {                                                                       \
        if (!expr) {                                                           \
            SDL_Log("SDL Error at %s: %d :%s\n", __FILE__, __LINE__,           \
                    SDL_GetError());                                           \
            goto cleanup;                                                      \
        }                                                                      \
    } while (0)

void programeInit(GameEngine *e) {
    _TRY(SDL_Init(SDL_INIT_VIDEO));
    e->data.window = SDL_CreateWindow("Hello", 800, 600, 0);
    _TRY(e->data.window);
    e->data.render = SDL_CreateRenderer(e->data.window, NULL);
    _TRY(e->data.render);
    _TRY(TTF_Init());
    return;
cleanup:
    if (e->data.window)
        SDL_DestroyWindow(e->data.window);
    if (e->data.render)
        SDL_DestroyRenderer(e->data.render);
    SDL_Quit();
    free(e);
    return;
}

void programeExit(GameEngine *e) {
    SDL_DestroyRenderer(e->data.render);
    SDL_DestroyWindow(e->data.window);
    SDL_Quit();
    free(e);
}

GameEngine *createEngine() {
    GameEngine *e = (GameEngine *)calloc(1, sizeof(GameEngine));
    if (!e) {
        SDL_Log("Error happens when Programe Init!\n");
        free(e);
        return NULL;
    }
    e->Init = programeInit;
    e->Exit = programeExit;
    return e;
}
