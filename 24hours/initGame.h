#ifndef _INIT_GAME__H
#define _INIT_GAME__H

void loadGame(GameState* game);
bool progress(SDL_Renderer* renderer, GameState* gameState, SDL_Window *window);
void doRender(SDL_Renderer* renderer, GameState* game /*Man* game = &man*/);

#endif // _INIT_GAME__H
