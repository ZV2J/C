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