#include "GameLoop.h"
#include "GameEngine.h"
#include "include/base.h"
#include "include/RenderText.h"

static bool ProgrameRunning = true;
static double bpm = 0.0;
static int division = 4;
static char buffer[32] = {0};
static int inputLen = 0;

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
    division    = 0;
    double timeOfBeat = 60.0 / bpm_local;
    double timeOfDivision = timeOfBeat / (double)division_local;
    RenderText(e, 100, 200, "Bpm: %.2f", bpm_local);
    RenderText(e, 100, 300, "Beat per sec:%.2fs", timeOfBeat);
    RenderText(e, 100, 350, "division per sec:%.4fs", timeOfDivision);
    RenderText(e, 100, 400, "Amount of beat per second:%lf", bpm / 60);
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