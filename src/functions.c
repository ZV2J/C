#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "bibli.h"

void SDL_ExitWithError(SDL_Window *p1, SDL_Renderer *p2, const char *message)
{
    SDL_DestroyRenderer(p2);
    SDL_DestroyWindow(p1);
    SDL_Log("ERROR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void SDL_LimitFPS(unsigned int limit)
{
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
        return;
    else if(limit > ticks + FPS_LIMIT)
        SDL_Delay(FPS_LIMIT);
    else
        SDL_Delay(limit - ticks);
}

void GetDeltaTime(int *delta)
{
    int NOW = SDL_GetPerformanceFrequency();
    int LAST = 0;

    *delta = NOW;
}