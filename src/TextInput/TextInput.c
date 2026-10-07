#include "TextInput.h"
#include <string.h>

void TextInput_Init(TextInput *this,
                    void (*on_change)(struct TextInput *, void *),
                    void *userData) {
    memset(this, 0, sizeof(this));
    this->cursor = 0;
    this->isFocused = false;
    this->isDirty = false;
    this->on_changed = on_change;
    this->userData = userData;
}

void TextInput_Clear(TextInput *this) {
    this->buffer[0] = '\0';
    this->cursor = 0;
    this->isDirty = true;
    if (this->on_changed)
        this->on_changed(this, this->userData);
    return;
}

void TextInput_Focus(TextInput *this) {
    this->isFocused = true;
}

void TextInput_Blur(TextInput *this) {
    this->isFocused = false;
}

bool TextInput_HitTest(const TextInput *this, float mouseX, float mouseY) {
    return mouseX >= this->x && mouseX <= this->x + this->w &&
           mouseY >= this->y && mouseY <= this->y + this->h;
}
bool TextInput_HandleEvent(TextInput *this, const SDL_Event *ev) {
    if (!this->isFocused)
        return false;
    switch (ev->type) {
        case SDL_EVENT_TEXT_INPUT:
            size_t curLen = strlen(this->buffer);
            size_t addLen = strlen(ev->text.text);
            if (curLen + addLen >= MAX_INPUT_LEN) {
                addLen = MAX_INPUT_LEN - curLen - 1;
            }
            // 简单追加到末尾（如需插入光标位置，见下方扩展）
            memcpy(this->buffer + curLen, ev->text.text, addLen);
            this->buffer[curLen + addLen] = '\0';
            this->cursor = (int)(curLen + addLen);
            this->isDirty = true;
            if (this->on_changed)
                this->on_changed(this, this->userData);
            return true;
        case SDL_EVENT_KEY_DOWN:
            if (ev->key.key == SDLK_BACKSPACE) {
                size_t len = strlen(this->buffer);
                if (len > 0) {
                    // 简化：删除最后一个字节（真实项目要按 UTF-8 字符边界删）
                    this->buffer[len - 1] = '\0';
                    this->cursor = (int)(len - 1);
                    this->isDirty = true;
                    if (this->on_changed)
                        this->on_changed(this, this->userData);
                }
                return true;
            }
            if (ev->key.key == SDLK_RETURN) {
                // 交给上层？这里可以触发"提交"回调
                return true;
            }
            break;

        default:
            break;
    }
    return false;
}
