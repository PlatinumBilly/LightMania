#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "base.h"

#include "GameEngine.h"

void GameLoop(GameEngine *e);

void everyDivisionTime(GameEngine *e, float bpm, int division);

void RenderText(GameEngine *e,char text[]);

#endif
