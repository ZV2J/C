#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "bibli.h"

int main(int argc, char **argv)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_ExitWithError(window, renderer, "init everything");

    if(SDL_CreateWindowAndRenderer(WIN_W, WIN_H, SDL_WINDOW_FULLSCREEN, &window, &renderer) != 0)
        SDL_ExitWithError(window, renderer, "create window + renderer");

    SDL_Surface *BackgroundSurface = NULL;
    SDL_Texture *BackgroundTexture = NULL;

    BackgroundSurface = SDL_LoadBMP("src/BackgroundSurface.bmp");

    if(BackgroundSurface == NULL)
        SDL_ExitWithError(window, renderer, "backgroundsurf");

    BackgroundTexture = SDL_CreateTextureFromSurface(renderer, BackgroundSurface);
    SDL_FreeSurface(BackgroundSurface);

    if(BackgroundTexture == NULL)
        SDL_ExitWithError(window, renderer, "backgroundtext");

    SDL_Rect BackgroundRect;

    if(SDL_QueryTexture(BackgroundTexture, NULL, NULL, &BackgroundRect.w, &BackgroundRect.h) != 0)
        SDL_ExitWithError(window, renderer, "query background");

    BackgroundRect.x = (WIN_W - BackgroundRect.w) / 2;
    BackgroundRect.y = (WIN_H - BackgroundRect.h) / 2;

    if(SDL_RenderCopy(renderer, BackgroundTexture, NULL, &BackgroundRect) != 0)
        SDL_ExitWithError(window, renderer, "rendercpy background");

    SDL_RenderPresent(renderer);

    SDL_bool program_launched = SDL_TRUE;

    while(program_launched)
    {
        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_SPACE:
                            program_launched = SDL_FALSE;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        printf("%d / %d\n", event.motion.x, event.motion.y);
                    break;

                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;

                default:
                    break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}