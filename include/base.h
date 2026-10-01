#ifndef BASE_H
#define BASE_H

//SDL基本的头文件
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

//标准库文件，或许以后会删掉
#include <stdio.h>
#include <stdlib.h>

//一个判断函数是否成功返回的宏定义（若失败需要goto cleanup）
#define __TRY(expr)                                                            \
    do {                                                                       \
        if (!expr) {                                                           \
            SDL_Log("SDL Error at %s: %d :%s\n", __FILE__, __LINE__,           \
                    SDL_GetError());                                           \
            goto cleanup;                                                      \
        }                                                                      \
    } while (0)

#endif
