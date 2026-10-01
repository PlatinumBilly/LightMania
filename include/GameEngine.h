#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "base.h"

//游戏的中关于SDL所用的地方的接口(对内使用，不对外公开)
typedef struct GameEngineData {
    SDL_Window        *window;
    SDL_Renderer      *render;
    TTF_Font          *font;
    SDL_Event         event;
} GameEngineData;

//游戏引擎，游戏的初始化与运行的统一调用接口
struct GameEngine {
    GameEngineData data;
    void (*Init)         (struct GameEngine *e);
    void (*Exit)         (struct GameEngine *e);
    void (*GameLoop)     (struct GameEngine *e);
};
typedef struct GameEngine GameEngine;

void ProgrameInit(GameEngine *e);

void ProgrameExit(GameEngine *e);

GameEngine *createEngine();

#endif
