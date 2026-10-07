#include "TextInputMgr.h"

// 初始化
void TextInputMgr_Init(TextInputMgr *mgr) {
    memset(mgr, 0, sizeof(TextInputMgr));
    mgr->input_Active = false;
    mgr->focused = NULL;
}

// 注册与销毁
void TextInputMgr_Add(TextInputMgr *mgr, TextInput *ti) {
    if (mgr->count < TEXT_INPUT_MAX_WIDGETS) {
        mgr->widgets[mgr->count++] = ti;
    } else {
        return;
    }
}
void TextInputMgr_Rem(TextInputMgr *mgr, TextInput *ti) {
    for (int i = 0; i < mgr->count; i++) {
        if (mgr->widgets[i] == ti) {
            for (int j = 0; j < mgr->count; j++)
                mgr->widgets[j] = mgr->widgets[j + 1];
            mgr->count--;
            if (mgr->focused == ti)
                mgr->focused = NULL;
            return;
        }
    }
}

static void set_Forced(TextInputMgr *mgr, TextInput *ti) {
    if (mgr->focused == ti)
        return;
    if (mgr->focused)
        TextInput_Blur(mgr->focused);
    mgr->focused = ti;
    if (ti)
        TextInput_Focus(ti);
}

void TextInputMgr_HandleEvent(TextInputMgr *mgr, SDL_Event *ev) {
    // 鼠标点击以确定焦点
    if (ev->type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
        ev->button.button == SDL_BUTTON_LEFT) {
        float mx = ev->button.x;
        float my = ev->button.y;
        TextInput *Hit = NULL;
        // 后面点击的优先添加
        for (int i = mgr->count - 1; i >= 0; i--) {
            if (TextInput_HitTest(mgr->widgets[i], mx, my)) {
                Hit = mgr->widgets[i];
                break;
            }
        }
        set_Forced(mgr, Hit);
        return;
    }
    if (mgr->focused) {
        TextInput_HandleEvent(mgr->focused, ev);
    }
}

// 同步SDL_StartTextInput的状态
void TextInputMgr_Update(TextInputMgr *mgr, SDL_Window *window) {
    bool need_Input = (mgr->focused != NULL);
    if (need_Input && !mgr->input_Active) {
        SDL_StartTextInput(window);
        mgr->input_Active = true;
    } else if (!need_Input && mgr->input_Active) {
        SDL_StopTextInput(window);
        mgr->input_Active = false;
    }
}