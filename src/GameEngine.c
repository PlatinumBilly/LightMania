#include "include/GameEngine.h"
#include "include/base.h"
#include "include/GameLoop.h"

void ProgrameInit(GameEngine *e) {
    __TRY(SDL_Init(SDL_INIT_VIDEO));
    e->data.window = SDL_CreateWindow("Hello", 800, 600, 0);
    __TRY(e->data.window);
    e->data.render = SDL_CreateRenderer(e->data.window, NULL);
    __TRY(e->data.render);
    __TRY(TTF_Init());
        e->data.font =
        TTF_OpenFont("/usr/share/fonts/truetype/ubuntu/UbuntuMono-B.ttf", 16);
    __TRY(e->data.font);
    SDL_StartTextInput(e->data.window);
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

void ProgrameExit(GameEngine *e) {
    SDL_DestroyRenderer(e->data.render);
    SDL_DestroyWindow(e->data.window);
    SDL_Quit();
    free(e);
    e = NULL;
}

GameEngine *createEngine() {
    GameEngine *e = (GameEngine *)calloc(1, sizeof(GameEngine));
    if (!e) {
        SDL_Log("Error happens when Programe Init!\n");
        free(e);
        return NULL;
    }
    e->Init = ProgrameInit;
    e->Exit = ProgrameExit;
    e->GameLoop = GameLoop;
    return e;
}
