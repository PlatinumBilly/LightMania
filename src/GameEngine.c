#include "include/GameEngine.h"
#include "include/base.h"

void programeInit(GameEngine *e) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("err:%s\n", SDL_GetError());
        return;
    }
    e->data.win = SDL_CreateWindow("Hello", 800, 600, 0);
    if (!e->data.win) {
        SDL_Log("err:%s\n", SDL_GetError());
        return;
    }
    e->data.ren = SDL_CreateRenderer(e->data.win, NULL);
    if (!e->data.ren) {
        SDL_Log("err:%s\n", SDL_GetError());
        return;
    }
    if (!TTF_Init()) {
        SDL_Log("err:%s\n", SDL_GetError());
        return;
    }
}

void programeExit(GameEngine *e) {
    SDL_DestroyRenderer(e->data.ren);
    SDL_DestroyWindow(e->data.win);
    SDL_Quit();
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
