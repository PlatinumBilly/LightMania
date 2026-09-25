#include "GameEngine.h"
#include "include/base.h"
#include "GameLoop.h"
void everyDivisionTime(GameEngine*e,float bpm,int division);

void gameLoop(GameEngine* e){
    float bpm;
    int division = 4;
    printf("Input bpm:");
    scanf("%f",&bpm);
    everyDivisionTime(e,bpm,division);
    return;
}

void everyDivisionTime(GameEngine* e,float bpm,int division){
    float timeOfBeat = 60.0000f/bpm;
    float timeOfDivision = timeOfBeat/division;
    e->data.font = TTF_OpenFont("arail.ttf", 24.0f);
    SDL_Color fg = {255,255,255,255};
    SDL_Surface *surface = TTF_RenderText_Blended(e->data.font, "Test", 0, fg);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(e->data.ren,surface);
    SDL_DestroySurface(surface);
    SDL_FRect dst = { 100.0f,100.0f,(float)texture->w,(float)texture->h};
    SDL_RenderTexture(e->data.ren,texture,NULL,&dst);
//    SDL_Log("Beat per ms:%.2fms\n",timeOfBeat);
//    SDL_Log("division per ms:%.4fms",timeOfDivision);
//    SDL_Log("Amount of beat per second:%.1f",bpm/60.0f);
    return;
}
