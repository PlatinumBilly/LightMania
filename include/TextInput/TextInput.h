#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include <stdbool.h>
#include "base.h"

#define MAX_INPUT_LEN 32

struct TextInput {
    char buffer[256]; // UTF-8文本
    int cursor;       // 光标位置
    bool isFocused;   // 获取窗口是否获得焦点
    bool isDirty;     // 检查内容是否改变

    void *userData;

    // 回调函数
    void (*on_changed)(struct TextInput *this, void *userData);

    float x, y, w, h;
};
typedef struct TextInput TextInput;

// 事件初始化
void TextInput_Init(TextInput *this,
                    void (*on_change)(struct TextInput *, void *),
                    void *userData);

// 事件的销毁
void TextInput_Clear(TextInput *this);

// 焦点控制
void TextInput_Focus(TextInput *this);
void TextInput_Blur(TextInput *this);

//单框事件处理（一般不直接使用）
bool TextInput_HandleEvent(TextInput* this,const SDL_Event *ev);

//判断鼠标是否在框内
bool TextInput_HitTest(const TextInput* this,float mouseX,float mouseY);

#endif