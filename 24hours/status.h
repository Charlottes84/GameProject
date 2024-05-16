#ifndef _STATUS__H
#define _STATUS__H

#include "defs.h"

void init_status_live(GameState *game);
void draw_status_lives(GameState *game);
void shutdown_status_lives(GameState *game);

void init_game_over(GameState *game);
void draw_game_over(GameState *game);
void shutdown_game_over(GameState *game);

void init_game_win(GameState *game);
void draw_game_win(GameState *game);
void shutdown_game_win(GameState *game);

void init_game_progressbar(GameState *game);
void draw_game_progressbar(GameState *game);
void shutdown_game_progressbar(GameState *game);

void init_game_menu(GameState *game);
void draw_game_menu(GameState *game);
void shutdown_game_menu(GameState *game);


#endif // _STATUS__H
