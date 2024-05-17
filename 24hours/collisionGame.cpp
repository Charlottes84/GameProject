#include <bits/stdc++.h>
#include "collisionGame.h"

#define BULLET_SPHERE_SIZE 17
#define AIM_BIRDS 100
#define BULLET_LASER_W 35
#define BULLET_LASER_H 8
#define BULLET_HEART 200

using namespace std;

int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2) {
    return (!((x1 > x2 + wt2) || (x2 > x1 + wt1) || (y1 > y2 + ht2) || (y2 > y1 + ht1)));
}

void collisionDetect(GameState* game)
{
    if(game->man.y >= SCREEN_HEIGHT - 70)
    {
        game->man.isDead = 1;
        Mix_PlayChannel(-1, game->dieSound, 0);
        Mix_HaltChannel(game->musicChannel);
    }

    for(int i = 0; i < NUM_BIRDS; i++)
    {
        float mw = BULLET_SPHERE_SIZE, mh = BULLET_SPHERE_SIZE;
        float mx = game->bullet.x, my = game->bullet.y;
        float bx = game->birds[i].x, by = game->birds[i].y, bw = BIRD_SIZE, bh = BIRD_SIZE;

        if(my + mh > by && my < by + bh)
        {
            if(mx < bx + bw && mx + mw > bx + bw)
            {
                game->bullet.x = bx + bw;
                mx = bx + bw;
            }
            else if(mx + mw > bx && mx < bx)
            {
                game->bullet.x = bx - mw;
                mx = bx - mw;

                game->bullet.is_move = false;
                game->bullet.collision = i;
                game->bullet.aim = true;

                game->bullet.x = -30;
                game->bullet.y = -30;

                game->birds[i].baseX = -AIM_BIRDS;
                game->birds[i].baseY = -AIM_BIRDS;
                Mix_PlayChannel(-1, game->collect, 0);
            }
        }
    }

    //ver2
    for(int i = 0; i < NUM_BIRDS; i++)
    {
        float mw = BULLET_LASER_W, mh = BULLET_LASER_H;
        float mx = game->bullet_laser.x, my = game->bullet_laser.y;
        float bx = game->bots[i].x, by = game->bots[i].y, bw = BIRD_SIZE, bh = BIRD_SIZE;

        if(my + mh > by && my < by + bh)
        {
            if(mx < bx + bw && mx + mw > bx + bw)
            {
                game->bullet_laser.x = bx + bw;
                mx = bx + bw;
            }
            else if(mx + mw > bx && mx < bx)
            {
                game->bullet_laser.x = bx - mw;
                mx = bx - mw;

                game->bullet_laser.is_move = false;
                game->bullet_laser.collision = i;
                game->bullet_laser.aim = true;

                game->bullet_laser.x = -10;
                game->bullet_laser.y = -10;

                game->bots[i].baseX = -AIM_BIRDS;
                game->bots[i].baseY = -AIM_BIRDS;
                Mix_PlayChannel(-1, game->collect, 0);
            }
        }
    }
    //ver3
    float mw = BULLET_HEART/2, mh = BULLET_HEART;
    float mx = game->bullet_heart.x, my = game->bullet_heart.y;
    float bx = game->prin.x, by = game->prin.y, bw = 50, bh = 80;

    if(my + mh > by && my < by + bh)
    {
        if(mx < bx + bw && mx + mw > bx + bw)
        {
            game->bullet_heart.x = bx + bw;
            mx = bx + bw;
        }
        else if(mx + mw > bx && mx < bx)
        {
            game->bullet_heart.x = bx - mw;
            mx = bx - mw;

            game->bullet_heart.is_move = false;
            game->bullet_heart.aim = true;

            game->bullet_heart.x = -150;
            game->bullet_heart.y = -150;
            Mix_PlayChannel(-1, game->collect, 0);

        }
    }

    for(int i = 0; i < NUM_BIRDS; i++)
    {
        if(collide2d(game->man.x, game->man.y, game->birds[i].x, game->birds[i].y, MANSIZE_W/1.5, MANSIZE_W/1.5, BIRD_SIZE/2, BIRD_SIZE/2))
        {
            Mix_PlayChannel(-1, game->dieSound, 0);
            game->man.isDead = 1;
            Mix_HaltChannel(game->musicChannel);
            break;
        }
        if(collide2d(game->man.x, game->man.y, game->bots[i].x, game->bots[i].y, MANSIZE_W/1.5, MANSIZE_W/1.5, BIRD_SIZE/2, BIRD_SIZE/2))
        {
            Mix_PlayChannel(-1, game->dieSound, 0);
            game->man.isDead = 1;
            Mix_HaltChannel(game->musicChannel);
            break;
        }
    }

    for(int i = 0; i < 100; i++)
    {
        float mw = MANSIZE_BASE_W, mh = MANSIZE_BASE_H;
        float mx = game->man.x, my = game->man.y;
        float bx = game->ledges[i].x, by = game->ledges[i].y,
              bw = game->ledges[i].w, bh = game->ledges[i].h;

        if(mx + mw/2 > bx && mx + mw/2 < bx + bw)
        {
            if(by < my && my < by + bh && game->man.dy < 0)
            {
                game->man.y = by + bh;
                my = by + bh;

                game->man.dy = 0;
                game->man.onLedge = 1;
                Mix_PlayChannel(-1, game->landSound, 0);
            }
        }

        if(mx + mw > bx && mx < bx + bw)
        {
            if(my + mh > by && my < by && game->man.dy > 0)
            {
                game->man.y = by - mh;
                my = by - mh;

                game->man.dy = 0;
                if(game->man.onLedge == 0)
                {
                    Mix_PlayChannel(-1, game->landSound, 0);
                    game->man.onLedge = 1;
                }
            }
        }

        if(my + mh > by && my < by + bh)
        {
            if(mx < bx + bw && mx + mw > bx + bw && game->man.dx < 0)
            {
                game->man.x = bx + bw;
                mx = bx + bw;

                game->man.dx = 0;
            }

            else if(mx + mw > bx && mx < bx && game->man.dx > 0)
            {
                game->man.x = bx - mw;
                mx = bx - mw;

                game->man.dx = 0;
            }
        }
    }
}

