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

    SDL_SetWindowTitle(window, "Program");

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

    SDL_Surface *PersonnageSurface = NULL;
    SDL_Texture *PersonnageTexture = NULL;

    PersonnageSurface = SDL_LoadBMP("src/PersonnageSurface.bmp");

    if(PersonnageSurface == NULL)
        SDL_ExitWithError(window, renderer, "persosurf");

    SDL_SetColorKey(PersonnageSurface, SDL_TRUE, SDL_MapRGB((*PersonnageSurface).format, 255, 255, 255));

    PersonnageTexture = SDL_CreateTextureFromSurface(renderer, PersonnageSurface);
    SDL_FreeSurface(PersonnageSurface);

    if(PersonnageTexture == NULL)
        SDL_ExitWithError(window, renderer, "persotext");

    SDL_Rect PersonnageRect;

    if(SDL_QueryTexture(PersonnageTexture, NULL, NULL, &PersonnageRect.w, &PersonnageRect.h) != 0)
        SDL_ExitWithError(window, renderer, "querytext perso");

    PersonnageRect.x = (WIN_W - PersonnageRect.w) / 2;
    PersonnageRect.y = (WIN_H - PersonnageRect.h) / 2;

    SDL_bool program_launched = SDL_TRUE;

    unsigned int frame_limit = 0;

    frame_limit = SDL_GetTicks() + FPS_LIMIT;
    SDL_LimitFPS(frame_limit);
    frame_limit = SDL_GetTicks() + FPS_LIMIT;

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
                        case SDLK_z:                                                       
                            PersonnageRect.y -= SPEED;                                                                        
                            if(PersonnageRect.y <= 0)
                            {
                                PersonnageRect.y += SPEED;                                
                                PersonnageRect.y += 0 - PersonnageRect.y;
                            }
                            break;

                        case SDLK_s:
                            PersonnageRect.y += SPEED;                            
                            if(PersonnageRect.y + PersonnageRect.h >= WIN_H)
                            {
                                PersonnageRect.y -= SPEED;                                
                                PersonnageRect.y -= PersonnageRect.h + PersonnageRect.y - WIN_H;
                            }
                            break;

                        case SDLK_q:
                            PersonnageRect.x -= SPEED;                            
                            if(PersonnageRect.x <= 0)
                            {
                                PersonnageRect.x += SPEED;                                
                                PersonnageRect.x += 0 - PersonnageRect.x;                                
                            }
                            break;

                        case SDLK_d:
                            PersonnageRect.x += SPEED;                            
                            if(PersonnageRect.x + PersonnageRect.w >= WIN_W)
                            {
                                PersonnageRect.x -= SPEED;                               
                                PersonnageRect.x -= PersonnageRect.w + PersonnageRect.x - WIN_W;
                            }
                            break;

                        case SDLK_SPACE:
                            program_launched = SDL_FALSE;
                            break;

                        default:
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                        printf(" X = %d | Y = %d\n", event.motion.x, event.motion.y);
                    break;

                case SDL_QUIT:
                    program_launched = SDL_FALSE;
                    break;

                default:

                    

                    if(SDL_RenderCopy(renderer, BackgroundTexture, NULL, &BackgroundRect) != 0)
                        SDL_ExitWithError(window, renderer, "rendercpy background");

                    if(SDL_RenderCopy(renderer, PersonnageTexture, NULL, &PersonnageRect) != 0)
                        SDL_ExitWithError(window, renderer, "rendercpy perso");

                    SDL_RenderPresent(renderer);

                    break;
            }
        }
    }

    SDL_DestroyTexture(PersonnageTexture);
    SDL_DestroyTexture(BackgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}