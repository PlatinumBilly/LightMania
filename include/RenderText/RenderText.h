#ifndef RENDERTEXT_H
#define RENDERTEXT_H

#include "GameEngine/GameEngine.h"


//RenderText 用于渲染文字或者变量到屏幕当中，支持像printf一样进行字符串格式化
void RenderText(GameEngine *e, int x, int y, const char *fmt, ...);

#endif