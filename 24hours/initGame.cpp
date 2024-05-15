#include <bits/stdc++.h>
#include "defs.h"
#include "status.h"

using namespace std;

/*-------------------------------- LOAD GAME --------------------------------*/
void loadGame(GameState* game)
{
    /*
    random_device rd;
    mt19937 gen(rd());

    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load("pic.png");
    if(Surpic == NULL)
    {
        cout << "Cannot find pic.png!" << endl;
        SDL_Quit();
        return;
    }

    game->pic = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    for(int i = 0; i < 100; i++)
    {
        uniform_int_distribution<int> dx(0, SCREEN_WIDTH);
        uniform_int_distribution<int> dy(0, SCREEN_HEIGHT);
        game->pics[i].x = dx(gen);
        game->pics[i].y = dy(gen);
    }
    */

    game->label = NULL;

    //Call Man
    game->man.x = 200, game->man.y = 200;
    game->man.dy = 0;
    //game->man.dx = 0;
    game->man.onLedge = 0;
    game->man.aniFrame = 0;
    game->time = 0;
    game->man.facingLeft = 1;
    game->man.slowingDown = 0;
    game->statusState = STATUS_STATE_LIVES;

    init_status_live(game);


    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load("img\\1.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\2.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\3.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[2] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\4.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[3] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\5.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[4] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\6.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[5] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\7.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[6] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load("img\\8.png");
    if(Surpic == NULL){
        cout << "Cannot find ManPic!" << endl;
        SDL_Quit();
        return;
    }
    game->manFrames[7] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    //Call Brick
    Surpic = IMG_Load("brick.png");
    if(Surpic == NULL){
        cout << "Cannot find Brick!" << endl;
        SDL_Quit();
        return;
    }

    game->brick = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

        //--init ledges
    for(int i = 0; i < 100; i++)
    {
        game->ledges[i].w = 300;
        game->ledges[i].h = 80;
        game->ledges[i].x = i*300;
        game->ledges[i].y = SCREEN_HEIGHT - 77;
    }
    game->ledges[99].x = 330;
    game->ledges[99].y = 250;

    //Load Fonts
    game->font = TTF_OpenFont("fonts\\Crazy-Pixel.ttf", 48);
    if(!game->font) {
        cout << "Can't find font file! \n";
        SDL_Quit();
        return;
    }

}

/*-------------------------------- PROGRESS --------------------------------*/
bool progress(SDL_Renderer* renderer, GameState* gameState, SDL_Window *window)
{
        bool done = false;

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
                                gameState->man.dy = -10;
                                gameState->man.onLedge = 0;
                        break;
            //-------------------------------------------------//
                    }
                } break;
                case SDL_QUIT:
                    done = true;
                break;
            }
        }

        const Uint8* Key = SDL_GetKeyboardState(NULL);

        //more jumping
        if(Key[SDL_SCANCODE_UP]){
            gameState->man.dy -= 0.3f;
        }
        /*
        if(Key[SDL_SCANCODE_DOWN]){
            gameState->man.y += SPEED;
        }
        */
        //
        if(Key[SDL_SCANCODE_RIGHT]){
        cout << "RIGHT" << " " << gameState->man.x << " " << gameState->man.dx << endl;
            gameState->man.dx += 0.5;
            if(gameState->man.dx > 6)
                gameState->man.dx = 6;
            gameState->man.facingLeft = 1;
            gameState->man.slowingDown = 0;
        }
        else if(Key[SDL_SCANCODE_LEFT]){
        cout << "LEFT" << " " << gameState->man.x << " " << gameState->man.dx << endl;
            gameState->man.dx -= 0.5;
            if(gameState->man.dx < -6)
                gameState->man.dx = -6;
            gameState->man.facingLeft = 0;
            gameState->man.slowingDown = 0;
        }
        else
        {
            // tạo ra ma sát
            gameState->man.aniFrame = 0;
            gameState->man.dx *= 0.8f;
            gameState->man.slowingDown = 1;
            if(fabsf(gameState->man.dx) < 0.1f)
                gameState->man.dx = 0;
        }
    return done;
}

/*-------------------------------- DO RENDER --------------------------------*/
void doRender(SDL_Renderer* renderer, GameState* game /*Man* game = &man*/)
{

    if(game->statusState == STATUS_STATE_LIVES) {
        draw_status_lives(game);
    }

    else if(game->statusState == STATUS_STATE_GAME)
    {
        //(*game).x = game -> x;
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        SDL_RenderClear(renderer); // clear the screen (to blue)

        /*
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rect = {pV->man.x, pV->man.y, 100, 100};
        SDL_RenderFillRect(renderer, &rect);

        for(int i = 0; i < 100; i++)
        {
            SDL_Rect picRect = {pV->pics[i].x, pV->pics[i].y, 50, 50};
            SDL_RenderCopy(renderer, pV->pic, NULL, &picRect);
        }
        */

        //draw ledges
        for(int i = 0; i < 100; i++)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_Rect ledgeRect = {game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
            SDL_RenderFillRect(renderer, &ledgeRect);
            SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
        }

        //draw a rectangle at man's position
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Rect rectMan = {game->man.x, game->man.y, MANSIZE, MANSIZE};
        //SDL_RenderFillRect(renderer, &rectMan);
        SDL_RenderCopyEx(renderer, game->manFrames[game->man.aniFrame]
                         , NULL, &rectMan, 0, NULL, (game->man.facingLeft == 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);

        /*
        const Uint8* Key = SDL_GetKeyboardState(NULL);
        if(Key[SDL_SCANCODE_RIGHT]){
            SDL_RenderCopyEx(renderer, game->manFrames[0], NULL, &rectMan, 0, NULL, SDL_FLIP_NONE);
            SDL_RenderPresent(renderer);
        }
        else if(Key[SDL_SCANCODE_LEFT]){
            SDL_RenderCopyEx(renderer, game->manFrames[0], NULL, &rectMan, 0, NULL, SDL_FLIP_HORIZONTAL);
            SDL_RenderPresent(renderer);
        }
        */
    }
    SDL_RenderPresent(renderer);
}
