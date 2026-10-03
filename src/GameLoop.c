#include "GameLoop.h"
#include "GameEngine.h"
#include "include/base.h"

static bool ProgrameRunning = true;

void CatchEvent(GameEngine *e);

void GameLoop(GameEngine *e) {
    // float bpm = 120.0f;
    // int division = 4;
    // int inputLen = 0;
    SDL_SetRenderDrawColor(e->data.render, 255, 255, 255, 255);
    while (ProgrameRunning) {
        CatchEvent(e);
        SDL_RenderClear(e->data.render);
        // RenderText(e, (char *)test, 200, 200);
        SDL_RenderPresent(e->data.render);
        SDL_Delay(20);
    }
    // printf("Input bpm:");
    // scanf("%f", &bpm);
    // everyDivisionTime(e, bpm, division);
    return;
}

void everyDivisionTime(GameEngine *e, float bpm, int division) {
    float timeOfBeat = 60.0000f / bpm;
    float timeOfDivision = timeOfBeat / division;
    SDL_Log("Beat per sec:%.2fs\n", timeOfBeat);
    SDL_Log("division per sec:%.4fs", timeOfDivision);
    SDL_Log("Amount of beat per second:%.1f", bpm / 60.0f);
    return;
}

void RenderText(GameEngine *e, const char text[], int x, int y) {
    SDL_Color fg = {0, 0, 0, 255};       // 前景颜色
    SDL_Color bg = {255, 255, 255, 255}; // 背景颜色
    SDL_Surface *sur = TTF_RenderText_LCD(e->data.font, text, 0, fg,
                                          bg); // 创建纹理，不过目前的泛用性过小
    SDL_Texture *tex = SDL_CreateTextureFromSurface(e->data.render, sur);
    float w, h;
    SDL_GetTextureSize(tex, &w, &h);
    SDL_DestroySurface(sur);
    SDL_FRect f = {x, y, w, h};
    SDL_RenderTexture(e->data.render, tex, NULL, &f);
    SDL_DestroyTexture(tex);
}

void CatchEvent(GameEngine *e) {
    static float bpm = 0.0f;
    int division = 4;
    static char buffer[32] = {0};
    static int inputLen = 0;
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
                    printf("bpm: %.2f\n", bpm);
                    buffer[0] = '\0';
                    inputLen = 0;
                }
                break;
            default:
                break;
        }

        // if (e->data.event.type == SDL_EVENT_QUIT) {
        //     running = false;
        // } else if (e->data.event.type == SDL_EVENT_TEXT_INPUT) {
        //     for (int i = 0; e->data.event.text.text[i] && inputLen < 31; i++)
        //     {
        //         buffer[inputLen++] = e->data.event.text.text[i];
        //         buffer[inputLen] = '\0';
        //     }

        // } else if (e->data.event.key.type == SDL_EVENT_KEY_DOWN) {
        //     if (e->data.event.key.key == SDLK_RETURN) {
        //         bpm = atoi(buffer);
        //         printf("bpm: %.2f\n", bpm);
        //         buffer[inputLen++] = '\0';
        //         inputLen = 0;
        //     }
        // }
    }
}