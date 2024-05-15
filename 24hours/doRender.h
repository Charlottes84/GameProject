#ifndef _DORENDER__H
#define _DORENDER__H

#include "status.h"


void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, GameState* game);

void doRender(SDL_Renderer* renderer, GameState* game);

#endif // _DORENDER__H
