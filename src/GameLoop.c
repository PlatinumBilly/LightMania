#include "GameLoop.h"
#include "GameEngine//GameEngine.h"
#include "include/RenderText/RenderText.h"
#include "include/base.h"

static bool ProgrameRunning = true;
static double bpm = 0.0;
static int division = 4;
static char inputBuffer[32] = { 0 };
static int inputLen = 0;

void CatchEvent(GameEngine* e);

void GameLoop(GameEngine* e)
{

    SDL_SetRenderDrawColor(e->data.render, 255, 255, 255, 255);
    while (ProgrameRunning) {
        CatchEvent(e);
        SDL_RenderClear(e->data.render);
        if (0 == strlen(inputBuffer)) { // 比较字符串是否为空
            strncpy(inputBuffer, "OwO", 32);
        }
        if(inputLen == 31){
            RenderText(e, 100, 300, "Too many word!");
        }
        RenderText(e, 100, 200, "%s", inputBuffer); // 仅作渲染测试
        SDL_RenderPresent(e->data.render);
        SDL_Delay(20);
    }
    // printf("Input bpm:");
    // scanf("%f", &bpm);
    // everyDivisionTime(e, bpm, division);
    return;
}

void everyDivisionTime(GameEngine* e, double bpm_local, int division_local)
{
    division = 0;
    double timeOfBeat = 60.0 / bpm_local;
    double timeOfDivision = timeOfBeat / (double)division_local;
    RenderText(e, 100, 200, "Bpm: %.2f", bpm_local);
    RenderText(e, 100, 300, "Beat per sec:%.2fs", timeOfBeat);
    RenderText(e, 100, 350, "division per sec:%.4fs", timeOfDivision);
    RenderText(e, 100, 400, "Amount of beat per second:%lf", bpm / 60);
    return;
}

void CatchEvent(GameEngine* e)
{
    while (SDL_PollEvent(&e->data.event)) {
        switch (e->data.event.type) {
        case SDL_EVENT_QUIT:
            SDL_Log("\n Quit event recevie.");
            ProgrameRunning = false;
            break;
        case SDL_EVENT_TEXT_INPUT:
            for (int i = 0; e->data.event.text.text[i] && inputLen < 31;
                i++) {
                inputBuffer[inputLen++] = e->data.event.text.text[i];
                inputBuffer[inputLen] = '\0';
            }
            break;
        case SDL_EVENT_KEY_DOWN:
            if (e->data.event.key.key == SDLK_RETURN) {
                inputBuffer[0] = '\0';
                inputLen = 0;
            }
            break;
        default:
            break;
        }
    }
}