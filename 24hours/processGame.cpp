#include <bits/stdc++.h>
#include "processGame.h"

#define BULLET_SPHERE_SPEED 10
#define REFILL_BULLET 400

using namespace std;

bool process(SDL_Renderer* renderer, GameState* gameState, SDL_Window *window)
{
    bool done = false;

    int joystickLeft = 0, joystickRight = 0, joystickButton1 = 0;

    if(gameState->joystick)
    {
        SDL_JoystickUpdate();

        if(SDL_JoystickGetAxis(gameState->joystick, 0) < -256)
          joystickLeft = 1;
        else if(SDL_JoystickGetAxis(gameState->joystick, 0) > 256)
          joystickRight = 1;

        if(SDL_JoystickGetButton(gameState->joystick, 0) || SDL_JoystickGetButton(gameState->joystick, 1) ||
           SDL_JoystickGetButton(gameState->joystick, 2))
        {
          joystickButton1 = 1;
        }
    }

    SDL_Event e;
    while(SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_WINDOWEVENT_CLOSE:
            {
                if(window)
                {
                    SDL_DestroyWindow(window);
                    window = NULL;
                    done = true;
                }
            } break;

            case SDL_KEYDOWN:
            {
                switch(e.key.keysym.sym)
                {
                    case SDLK_SPACE:
                        done = true;
                    break;
        //------------------ Important !!! ------------------//
                    case SDLK_UP:
                        cout << "UP" << " " << gameState->man.y << " " << gameState->man.dy << endl;
                        if(gameState->man.onLedge)
                        {
                            gameState->man.dy = -7;
                            gameState->man.onLedge = 0;
                            Mix_PlayChannel(-1, gameState->JumpSound, 0);
                        }
                    break;
        //-------------------------------------------------//
                }
            } break;
            case SDL_QUIT:
                done = true;
            break;
        }
    }

    if(gameState->man.onLedge && joystickButton1)
    {
        gameState->man.dy = -8;
        gameState->man.onLedge = 0;
        Mix_PlayChannel(-1, gameState->JumpSound, 0);
    }

    const Uint8* Key = SDL_GetKeyboardState(NULL);

    //bullet ready
    if(Key[SDL_SCANCODE_K])
    {
        gameState->bullet.is_move = true;

        if(gameState->bullet.cnt == 0)
        {
            gameState->bullet.x = gameState->man.x + MANSIZE/2;
            gameState->bullet.y = gameState->man.y + MANSIZE/2;
            gameState->bullet.cnt = 1;
            gameState->bullet.time = gameState->bullet.x;
        }
        else if(gameState->bullet.cnt == 1 /*&& gameState->bullet.time + REFILL_BULLET < gameState->time*/)
        {
            gameState->bullet.x = gameState->man.x + MANSIZE/2;
            gameState->bullet.y = gameState->man.y + MANSIZE/2;
            gameState->bullet.time = gameState->bullet.x;
        }
    }

    if(gameState->bullet.is_move == true)
    {
        gameState->bullet.x += BULLET_SPHERE_SPEED;
        int x = gameState->bullet.x;
        if(gameState->bullet.time + REFILL_BULLET < x || gameState->bullet.aim == true)
        {
            gameState->bullet.x = -10;
            gameState->bullet.y = -10;
            gameState->bullet.is_move = false;
            gameState->bullet.aim = false;
            //gameState->bullet.ready = true;
        }

    }

    //more jumping
    if(Key[SDL_SCANCODE_UP] || joystickButton1){
        gameState->man.dy -= 0.3f;
    }

    if(Key[SDL_SCANCODE_RIGHT] || joystickRight){
    cout << "RIGHT" << " " << gameState->man.x << " " << gameState->man.dx << endl;
        gameState->man.dx += 0.5;
        if(gameState->man.dx > 6)
            gameState->man.dx = 6;
        gameState->man.facingLeft = 1;
        gameState->man.slowingDown = 0;
        //Mix_PlayChannel(-1, gameState->landSound, 0);
    }
    else if(Key[SDL_SCANCODE_LEFT] || joystickLeft){
    cout << "LEFT" << " " << gameState->man.x << " " << gameState->man.dx << endl;
        gameState->man.dx -= 0.5;
        if(gameState->man.dx < -6)
            gameState->man.dx = -6;
        gameState->man.facingLeft = 0;
        gameState->man.slowingDown = 0;
        //Mix_PlayChannel(-1, gameState->landSound, 0);
    }
    else
    {
        // tạo ra ma sát
        gameState->man.currentFrames = 0;
        gameState->man.dx *= 0.8f;
        gameState->man.slowingDown = 1;
        if(fabsf(gameState->man.dx) < 0.1f)
            gameState->man.dx = 0;
    }
    return done;
}

void Move(GameState *game)
{
    if(game->statusState == STATUS_STATE_MENU)
    {
        const Uint8* Key = SDL_GetKeyboardState(NULL);
        if(Key[SDL_SCANCODE_J])
        {
            shutdown_game_menu(game);
            game->statusState = STATUS_STATE_LIVES;
            init_status_live(game);
            game->check = true;
        }
    }
    if(game->check == true) game->time++;

    if(game->statusState == STATUS_STATE_LIVES)
    {
        if(game->time > 120)
        {
            shutdown_status_lives(game);
            game->statusState = STATUS_STATE_GAME;
            game->musicChannel = Mix_PlayChannel(-1, game->bgMusics, -1);
        }
    }
    else if(game->statusState == STATUS_STATE_GAMEOVER)
    {
        if(game->time > 190)
        {
            SDL_Quit();
            exit(0);
        }
    }

    else if(game->statusState == STATUS_STATE_GAME) {
        if(game->man.isDead == 0)
        {
            init_game_progressbar(game);
            Character *Fake_Man = &game->man;

            Fake_Man->x += Fake_Man->dx;
            Fake_Man->y += Fake_Man->dy;

            if(Fake_Man->dx != 0 && Fake_Man->onLedge && Fake_Man->slowingDown == 0)
            {
                if(game->time % 8 == 0)
                {
                    if(Fake_Man->currentFrames == 0)
                        Fake_Man->currentFrames = 1;
                    else if(Fake_Man->currentFrames == 1)
                        Fake_Man->currentFrames = 2;
                    else if(Fake_Man->currentFrames == 2)
                        Fake_Man->currentFrames = 3;
                    else if(Fake_Man->currentFrames == 3)
                        Fake_Man->currentFrames = 4;
                    else if(Fake_Man->currentFrames == 4)
                        Fake_Man->currentFrames = 5;
                    else if(Fake_Man->currentFrames == 5)
                        Fake_Man->currentFrames = 6;
                    else if(Fake_Man->currentFrames == 6)
                        Fake_Man->currentFrames = 7;
                    else
                        Fake_Man->currentFrames = 0;
                }
            }

            if(Fake_Man->x > LIMIT_X)
            {
                init_game_win(game);
                game->statusState = STATUS_STATE_WINGAME;
            }

            Fake_Man->dy += GRAVITY;

            /* bird move*/
            for(int i = 0; i < NUM_BIRDS; i++)
            {
                game->birds[i].x = game->birds[i].baseX;
                game->birds[i].y = game->birds[i].baseY;

                if(game->birds[i].mode == 0)
                {
                  game->birds[i].x = game->birds[i].baseX+sinf(game->birds[i].phase+game->time*0.06f)*90;
                }
                else
                {
                  game->birds[i].y = game->birds[i].baseY+cosf(game->birds[i].phase+game->time*0.06f)*90;
                }
            }

        }
        if(game->man.isDead == 1 && game->deathCountdown < 0)
        {
            game->deathCountdown = 120;
        }
        if(game->deathCountdown >= 0)
        {
            game->deathCountdown--;
            if(game->deathCountdown < 0) {
                game->man.lives--;
                if(game->man.lives > 0)
                {
                    init_status_live(game);
                    game->statusState = STATUS_STATE_LIVES;

                    game->time = 0;

                    game->man.isDead = 0;
                    game->man.x = 100;
                    game->man.y = 240 - 40;
                    game->man.dx = 0;
                    game->man.dy = 0;

                    game->bullet.x = -10;
                    game->bullet.y = -10;
                    game->bullet.time = 0;
                    game->bullet.is_move = false;
                    game->bullet.ready = false;
                    game->bullet.cnt = 0;
                    game->bullet.aim = false;
                    game->bullet.x_fake = 0;
                    game->bullet.y_fake = 0;
                    game->bullet.collision = 0;

                    initStars(game);
                }
                else
                {
                    init_game_over(game);
                    game->statusState = STATUS_STATE_GAMEOVER;
                    game->time = 0;
                }
            }
        }
    }

    game->scrollX = -game->man.x + 320;
    if(game->scrollX > 0)
        game->scrollX = 0;
    if(game->scrollX < -LIMIT_X+320)
        game->scrollX = -LIMIT_X+320;
}
