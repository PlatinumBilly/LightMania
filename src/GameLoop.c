#include "GameLoop.h"
#include "GameEngine.h"
#include "include/base.h"

void GameLoop(GameEngine *e) {
    float bpm = 120.0f;
    int division = 4;
    bool running = true;
    char inputBuffer[1024] = {0};
    int bufferLen = 0;
    SDL_SetRenderDrawColor(e->data.render, 255, 255, 255, 255);
    while (running) {
        while (SDL_PollEvent(&e->data.event)) {
            if (e->data.event.type == SDL_EVENT_QUIT)
                running = false;
        }
        SDL_RenderClear(e->data.render);
        RenderText(e, "The fitst beat time:", 200, 200);
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
    SDL_Color fg = {0, 0, 0, 255};
    SDL_Color bg = {255, 255, 255, 255};
    SDL_Surface *sur = TTF_RenderText_LCD(e->data.font, text, 0, fg, bg);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(e->data.render, sur);
    float w, h;
    SDL_GetTextureSize(tex, &w, &h);
    SDL_DestroySurface(sur);
    SDL_FRect f = {x, y, w, h};
    SDL_RenderTexture(e->data.render, tex, NULL, &f);
    SDL_DestroyTexture(tex);
}