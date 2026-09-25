#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "SDL3_ttf/SDL_ttf.h"
#include "base.h"

typedef struct GameEngineData{
  SDL_Window *win;
  SDL_Renderer *ren;
  TTF_Font* font;
}GameEngineData;

struct GameEngine {
  GameEngineData data;
  void (*Init)(struct GameEngine* e);
  void (*Exit)(struct GameEngine* e);
};
typedef struct GameEngine GameEngine;

void programeInit(GameEngine *e);

void programeExit(GameEngine *e);

GameEngine* createEngine();

#endif
