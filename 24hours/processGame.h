#ifndef _PROCESSGAME__H
#define _PROCESSGAME__h

#include "loadGame.h"

bool process(SDL_Renderer* renderer, GameState* gameState, SDL_Window *window);
void Move(GameState *game);

#endif // _PROCESSGAME__H
