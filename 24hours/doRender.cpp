#include <bits/stdc++.h>
#include "doRender.h"

#define BULLET_SPHERE_SIZE 17
#define BULLET_LASER_W 35
#define BULLET_LASER_H 8
#define BULLET_HEART 200

using namespace std;

const int GOKU_CLIPS[][4] = {
    {0, 0, 128, 128},
    {127, 0, 128, 128},
    {255, 0, 128, 128},
    {383, 0, 128, 128},
    {511, 0, 128, 128},
    {639, 0, 128, 128},
    {767, 0, 128, 128},
    {895, 0, 128, 128},
};
const int GOKU_FRAMES = sizeof(GOKU_CLIPS)/sizeof(int)/4;

const int PRINCESS_CLIPS[][4] = {
    {0, 0, 50, 80},
    {49, 0, 50, 80},
    {99, 0, 50, 80},
    {149, 0, 50, 80},
    {199, 0, 50, 80},
    {249, 00, 50, 80},
};
const int PRINCESS_FRAMES = sizeof(PRINCESS_CLIPS)/sizeof(int)/4;

const int PIG_CLIPS[][4] = {
    {0, 0, 48, 48},
    {47, 0, 48, 48},
    {95, 0, 48, 48},
    {143, 0, 48, 48},
    {191, 0, 48, 48},
    {239, 0, 48, 48},
    {287, 0, 48, 48},
};
const int PIG_FRAMES = sizeof(PIG_CLIPS)/sizeof(int)/4;

void RenderHPBar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor, GameState* game) {

    SDL_Renderer *Renderer = game->renderer;

    Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : (1-Percent);

    SDL_Rect bgrect = { x, y, w, h };
    SDL_SetRenderDrawColor(Renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(Renderer, &bgrect);

    SDL_SetRenderDrawColor(Renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int)((float)w * (Percent));
    int px = x + (w - pw);
    SDL_Rect fgrect = {px, y, pw, h};
    SDL_RenderFillRect(Renderer, &fgrect);
    draw_game_progressbar(game);
}

void doRender(SDL_Renderer* renderer, GameState* game)
{
    if(game->statusState == STATUS_STATE_MENU) {
        draw_game_menu(game);
    }
    else if(game->statusState == STATUS_STATE_CONTROL) {
        draw_game_control(game);
    }
    else if(game->statusState == STATUS_STATE_LIVES) {
        draw_status_lives(game);
    }
    else if(game->statusState == STATUS_STATE_GAMEOVER) {
        draw_game_over(game);
    }
    else if(game->statusState ==  STATUS_STATE_WINGAME) {
        draw_game_win(game);
    }
    else if(game->statusState == STATUS_STATE_GAME)
    {
        SDL_RenderClear(renderer);

        //background
        for(int i = 0; i < 100; i++)
        {
            SDL_Rect ledgeRect = {game->scrollX + game->BK[i].x, game->BK[i].y, game->BK[i].w, game->BK[i].h};
            SDL_RenderCopy(renderer, game->background, NULL, &ledgeRect);
        }

        //draw ledges
        for(int i = 0; i < NUM_LEDGES-20; i++)
        {
            SDL_Rect ledgeRect = {game->scrollX + game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
            SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
        }

        //Bird
        int a = game->bullet.collision;
        int b = game->bullet_laser.collision;
        for(int i = 0; i < NUM_BIRDS; i++)
        {
            SDL_Rect picRect = {game->scrollX + game->birds[i].x, game->birds[i].y, 50, 50};
            SDL_RenderCopy(renderer, game->bird, NULL, &picRect);

            SDL_Rect botRect = {game->scrollX + game->bots[i].x, game->bots[i].y, 50, 50};
            SDL_RenderCopyEx(renderer, game->bot, NULL, &botRect, 0, NULL, SDL_FLIP_HORIZONTAL);
        }

        SDL_Rect rect = {game->scrollX +  game->birds[a].x,  game->birds[a].y - 25, FIRE_W, FIRE_H};
        SDL_RenderCopyEx(renderer, game->fire, NULL, &rect, 0, NULL, (game->time%20 < 10) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        SDL_Rect rect1 = {game->scrollX +  game->bots[b].x,  game->bots[b].y - 25, FIRE_W, FIRE_H};
        SDL_RenderCopyEx(renderer, game->fire, NULL, &rect1, 0, NULL, (game->time%20 < 10) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);


        //draw a rectangle at man's position
        int i = game->man.currentFrames;
        SDL_Rect clip = {GOKU_CLIPS[i][0], GOKU_CLIPS[i][1], MANSIZE_BASE, MANSIZE_BASE};
        SDL_Rect rectMan = {game->scrollX + game->man.x, game->man.y, MANSIZE_BASE, MANSIZE_BASE};
        SDL_RenderCopyEx(renderer, game->manFrames[game->man.currentFrames]
                         , &clip, &rectMan, 0, NULL, (game->man.facingLeft == 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        //SDL_RenderFillRect(renderer, &rectMan);

        //Bullet_Sphere
        SDL_Rect Bullet_Rect = {game->bullet.x + game->scrollX, game->bullet.y, BULLET_SPHERE_SIZE, BULLET_SPHERE_SIZE};
        SDL_RenderCopy(renderer, game->sphere, NULL, &Bullet_Rect);

        SDL_Rect Bullet_laser = {game->bullet_laser.x + game->scrollX, game->bullet_laser.y, BULLET_LASER_W, BULLET_LASER_H};
        SDL_RenderCopy(renderer, game->laser, NULL, &Bullet_laser);

        SDL_Rect Bullet_heart = {game->bullet_heart.x + game->scrollX, game->bullet_heart.y, BULLET_HEART, BULLET_HEART};
        SDL_RenderCopy(renderer, game->bul_heart, NULL, &Bullet_heart);

        //Princess
        int j = game->prin.currentFrames;
        SDL_Rect prin_clip = {PRINCESS_CLIPS[j][0], PRINCESS_CLIPS[j][1], 50, 80};
        SDL_Rect prin_rect = {game->scrollX + game->prin.x, game->prin.y, 50, 80};
        SDL_RenderCopyEx(renderer, game->princess[j], &prin_clip, &prin_rect, 0, NULL, (game->prin.facingleft == 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        bool check_win = false;
        if(game->bullet_heart.aim == true)
        {
            int z = game->pi.currentFrames;
            SDL_Rect pi_clip = {PIG_CLIPS[z][0], PIG_CLIPS[z][1], 48, 48};
            SDL_Rect pi_rect = {game->scrollX + game->man.x, game->man.y - 20, 155, 150};
            SDL_RenderCopy(renderer, game->pig[z], &pi_clip, &pi_rect);
            check_win = true;
        }
        if(check_win == true) game->pi.time++;

        if(game->man.isDead == 1)
        {
            SDL_Rect rect = {game->scrollX + game->man.x, game->man.y - 25, FIRE_W, FIRE_H};
            SDL_RenderCopyEx(renderer, game->fire, NULL, &rect, 0, NULL, (game->time%20 < 10) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
        }

        SDL_Color white = {255, 255, 255, 255};
        SDL_Color black = {0, 0, 0, 255};
        RenderHPBar(250, 5, 400, 30, (game->man.x)/(FINISH), black, white, game);
    }
    SDL_RenderPresent(renderer);
}
