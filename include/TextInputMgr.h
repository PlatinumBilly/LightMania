#ifndef TEXTINPUTMGR_H
#define TEXTINPUTMGR_H

#include "TextInput.h"
#include "base.h"

#define TEXT_INPUT_MAX_WIDGETS 16

typedef struct TextInputMgr {
    TextInput *widgets[TEXT_INPUT_MAX_WIDGETS];
    int count;
    TextInput *focused; // 当前聚焦的输入框
    bool input_Active;  // 判断是否聚焦
} TextInputMgr;

// 初始化
void TextInputMgr_Init(TextInputMgr *mgr);

// 注册与销毁
void TextInputMgr_Add(TextInputMgr *mgr, TextInput *ti);
void TextInputMgr_Rem(TextInputMgr *mgr, TextInput *ti); // Rem(Remove)

void TextInputMgr_HandleEvent(TextInputMgr *mgr, SDL_Event *ev);

// 同步SDL_StartTextInput的状态
void TextInputMgr_Update(TextInputMgr *mgr,SDL_Window* window);

#endif