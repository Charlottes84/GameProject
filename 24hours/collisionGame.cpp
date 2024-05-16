#include <bits/stdc++.h>
#include "collisionGame.h"

#define BULLET_SPHERE_SIZE 10
#define AIM_BIRDS 100

using namespace std;

//useful utility function to see if two rectangles are colliding at all
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
        //exit(0);
    }

    for(int i = 0; i < NUM_BIRDS; i++)
    {
        float mw = BULLET_SPHERE_SIZE, mh = BULLET_SPHERE_SIZE;
        float mx = game->bullet.x, my = game->bullet.y;
        float bx = game->birds[i].x, by = game->birds[i].y, bw = BIRD_SIZE, bh = BIRD_SIZE;

        if(my + mh > by && my < by + bh)
        {
            // check phải của đất
            if(mx < bx + bw && mx + mw > bx + bw)
            {
                game->bullet.x = bx + bw;
                mx = bx + bw;
            }
            else if(mx + mw > bx && mx < bx)
            {
                game->bullet.x = bx - mw;
                mx = bx - mw;

                game->bullet.y_fake = game->birds[i].y;
                game->bullet.x_fake = game->birds[i].x;

                game->bullet.is_move = false;
                game->bullet.collision = i;
                game->bullet.aim = true;

                game->bullet.x = -10;
                game->bullet.y = -10;

                game->birds[i].baseX = -AIM_BIRDS;
                game->birds[i].baseY = -AIM_BIRDS;
                //cout << i << endl;
            }
        }
    }

    for(int i = 0; i < NUM_BIRDS; i++)
    {
        if(collide2d(game->man.x, game->man.y, game->birds[i].x, game->birds[i].y, MANSIZE/1.5, MANSIZE/1.5, BIRD_SIZE/2, BIRD_SIZE/2))
        {
            Mix_PlayChannel(-1, game->dieSound, 0);
            game->man.isDead = 1;
            Mix_HaltChannel(game->musicChannel);
            break;
        }
    }

    //check for collision with any ledges (brick blocks) - kiểm tra va chạm với bất kỳ vật nào
    for(int i = 0; i < 100; i++)
    {
        float mw = MANSIZE, mh = MANSIZE;
        float mx = game->man.x, my = game->man.y;
        float bx = game->ledges[i].x, by = game->ledges[i].y,
              bw = game->ledges[i].w, bh = game->ledges[i].h;

        /*
        if(my + mh > by && my < by + bh)
        {
            // rubbing against right edge - cọ sát vào cạnh phải
            if(mx < bx + bw && mx + mw > bx + bw)
            {
                //correct x
                game->man.x = bx + bw;
                mx = bx + bw;
            }

            // rubbing against left edge
            else if(mx + mw > bx && mx < bx)
            {
                //correct x
                game->man.x = bx - mw;
                mx = bx - mw;
            }
        }
        */

        /*
        // check height
        if(my + mh > by && my < by + bh)
        {
            //height left
            if(mx + mw > bx && mx < bx)
            {
                game->man.x = bx - mw;
                game->man.x = bx + bw;
                mx = bx - mw;
            }
            //height right
            else if(bx + bw < mx + mw && bx + bw > mx)
            {
                game->man.x = bx + bw;
                mx = bx + bw;
            }
        }
        */

        /*
        if(mx + mw > bx && mx < bx + bw)
        {
            //are we bumping our head?
            if(my < by + bh && my > by)
            {
                //correct y
                game->man.y = by + bh;
                // bumped our head, stop any jump velocity
                game->man.dy = 0;
                game->man.onLedge = 1;
            }
            else if(my + mh > by && my < by)
            {
                //correct y
                game->man.y = by - mh;

                // landed on this ledge, stop any jump velocity
                game->man.dy = 0;
                game->man.onLedge = 1;
            }
        }
        */

        if(mx + mw/2 > bx && mx + mw/2 < bx + bw)
        {
            // man chạm đầu vào đáy đá
            if(by < my && my < by + bh && game->man.dy < 0)
            {
                game->man.y = by + bh;
                my = by + bh;

                game->man.dy = 0; // nếu bị đập đầu vào tường (đáy đá) thì bị đập xuống (giới hạn)
                game->man.onLedge = 1;
                Mix_PlayChannel(-1, game->landSound, 0);
            }
            /*
            else if(my < by && my + mh > by)
            {
                game->man.y = by - mh;
                game->man.dy = 0;
                game->man.onLedge = 1;
            }
            */
        }
        // đứng trên đất
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

        //check chạm hai cạnh
        if(my + mh > by && my < by + bh)
        {
            // check phải của đất
            if(mx < bx + bw && mx + mw > bx + bw && game->man.dx < 0)
            {
                game->man.x = bx + bw;
                mx = bx + bw;

                game->man.dx = 0;
            }
            //check chạm trái
            else if(mx + mw > bx && mx < bx && game->man.dx > 0)
            {
                game->man.x = bx - mw;
                mx = bx - mw;

                game->man.dx = 0;
            }
        }
    }
}

