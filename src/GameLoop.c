#include "GameLoop.h"
#include "GameEngine.h"
#include "include/base.h"

static bool ProgrameRunning = true;
static double bpm = 0.0;
static int division = 4;
static char buffer[32] = {0};
static int inputLen = 0;
struct Input {
    char buffer[32];
    int inputLen;
};

void CatchEvent(GameEngine *e);

void GameLoop(GameEngine *e) {
    SDL_SetRenderDrawColor(e->data.render, 255, 255, 255, 255);
    while (ProgrameRunning) {
        CatchEvent(e);
        SDL_RenderClear(e->data.render);
        //        RenderText(e, 100, 200, "Input a bpm");
        everyDivisionTime(e, bpm, 4);
        SDL_RenderPresent(e->data.render);
        SDL_Delay(20);
    }
    // printf("Input bpm:");
    // scanf("%f", &bpm);
    // everyDivisionTime(e, bpm, division);
    return;
}

void everyDivisionTime(GameEngine *e, double bpm_local, int division_local) {
    division = 0;
    double timeOfBeat = 60.0 / bpm_local;
    double timeOfDivision = timeOfBeat / (double)division_local;
    RenderText(e, 100, 200, "Bpm: %.2f", bpm_local);
    RenderText(e, 100, 300, "Beat per sec:%.2fs", timeOfBeat);
    RenderText(e, 100, 350, "division per sec:%.4fs", timeOfDivision);
    RenderText(e, 100, 400, "Amount of beat per second:%lf", bpm / 60);
    return;
}

void RenderText(GameEngine *e, int x, int y, const char *fmt, ...) {
    SDL_Color fg = {0, 0, 0, 255};       // 前景颜色
    SDL_Color bg = {255, 255, 255, 255}; // 背景颜色
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
    SDL_Surface *sur = TTF_RenderText_LCD(e->data.font, buff, len, fg,
                                          bg); // 创建纹理
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

void CatchEvent(GameEngine *e) {
    while (SDL_PollEvent(&e->data.event)) {
        switch (e->data.event.type) {
            case SDL_EVENT_QUIT:
                ProgrameRunning = false;
                break;
            case SDL_EVENT_TEXT_INPUT:
                for (int i = 0; e->data.event.text.text[i] && inputLen < 31;
                     i++) {
                    buffer[inputLen++] = e->data.event.text.text[i];
                    buffer[inputLen] = '\0';
                }
                break;
            case SDL_EVENT_KEY_DOWN:
                if (e->data.event.key.key == SDLK_RETURN) {
                    bpm = atoi(buffer);
                    // printf("BPM: %d\n", bpm);
                    buffer[0] = '\0';
                    inputLen = 0;
                }
                break;
            default:
                break;
        }
    }
}