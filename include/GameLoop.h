#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "base.h"

#include "GameEngine.h"

//游戏主逻辑运行的地方，由main.c引入
void GameLoop(GameEngine *e);

//输出每一小节的时间，暂时放在这里
void everyDivisionTime(GameEngine *e, int bpm, int division,int n);

//封装函数，用于渲染指定文字到指定地方
void RenderText(GameEngine *e, int x, int y,const char* fmt, ...);

#endif
