#include "include/GameEngine.h"
#include "include/GameLoop.h"
#include "include/base.h"

void ProgrameInit(GameEngine *e) {
    __TRY(SDL_Init(SDL_INIT_VIDEO));
    e->data.window =
        SDL_CreateWindow("Hello", 800, 600, SDL_WINDOW_ALWAYS_ON_TOP);
    __TRY(e->data.window);
    e->data.render = SDL_CreateRenderer(e->data.window, NULL);
    __TRY(e->data.render);
    __TRY(TTF_Init());
    e->data.font =
        TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf",
                     16); // 该字体仅作为临时测试使用
    __TRY(e->data.font);
    return;
cleanup:
    if (e->data.window)
        SDL_DestroyWindow(e->data.window);
    if (e->data.render)
        SDL_DestroyRenderer(e->data.render);
    SDL_Quit();
    free(e);
    e = NULL;
    return;
}

void ProgrameExit(GameEngine *e) {
    SDL_DestroyRenderer(e->data.render);
    SDL_DestroyWindow(e->data.window);
    SDL_Quit();
    TTF_Quit();
}

void DestroyEngine(GameEngine *e) {
    free(e);
    e = NULL;
}

GameEngine *createEngine() {
    GameEngine *e = calloc(1, sizeof(GameEngine));
    e->Init          =    ProgrameInit;
    e->Exit          =    ProgrameExit;
    e->GameLoop      =    GameLoop;
    e->DestoryEngine =    DestroyEngine;
    return e;
}
