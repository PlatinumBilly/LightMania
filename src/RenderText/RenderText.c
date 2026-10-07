#include "RenderText/RenderText.h"
#include "base.h"

void RenderText(GameEngine *e, int x, int y, const char *fmt, ...) {
    SDL_Color fg = {0, 0, 0, 255};       // 前景颜色
    va_list args, args_copy;
    va_start(args, fmt);
    va_copy(args_copy, args);

    // 计算缓冲区大小
    size_t len = (size_t)vsnprintf(NULL, 0, fmt, args_copy);
    va_end(args_copy);
    if (len < 0) {
        va_end(args);
        return;
    }
    // 分配缓冲区
    char *buff = (char *)malloc(len + 1);
    if (!buff) {
        va_end(args);
        return;
    }

    // 格式化
    vsnprintf(buff, len + 1, fmt, args);
    va_end(args);
    SDL_Surface *sur =
        TTF_RenderText_Blended(e->data.font, buff, len, fg); // 创建纹理
    SDL_Texture *tex = SDL_CreateTextureFromSurface(e->data.render, sur);
    float w, h;
    SDL_GetTextureSize(tex, &w, &h);
    SDL_DestroySurface(sur);
    SDL_FRect f = {(float)x, (float)y, w, h};
    SDL_RenderTexture(e->data.render, tex, NULL, &f);
    SDL_DestroyTexture(tex);
    free(buff);
    return;
}