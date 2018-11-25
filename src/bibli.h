#ifndef __BIBLI__H__
#define __BIBLI__H__

#define WIN_W 1920
#define WIN_H 1080
#define SPEED 10
#define FPS_LIMIT 1000 / 144

void SDL_ExitWithError(SDL_Window *p1, SDL_Renderer *p2, const char *message);
void SDL_LimitFPS(unsigned int limit);

#endif
