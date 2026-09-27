#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "base.h"

typedef struct GameEngineData {
    SDL_Window        *window;
    SDL_Renderer      *render;
    TTF_Font          *font;
    SDL_Event         event;
} GameEngineData;

struct GameEngine {
    GameEngineData data;
    void (*Init)         (struct GameEngine *e);
    void (*Exit)         (struct GameEngine *e);
    void (*GameLoop)     (struct GameEngine *e);
};
typedef struct GameEngine GameEngine;

void programeInit(GameEngine *e);

void programeExit(GameEngine *e);

GameEngine *createEngine();

#endif
