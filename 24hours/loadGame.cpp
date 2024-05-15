#include <bits/stdc++.h>
#include "loadGame.h"

using namespace std;

const char* GOKU_SPRITE_FILE = "img\\Walk.png";
const char* FIRE_FILE = "fire.png";
const char* WHITE_BIRD_FILE = "whitebird.png";
const char* HEART_FILE = "heart.png";
const char* BACKGROUND_FILE = "assets\\img\\background.png";
const char* BRICK_FILE = "assets\\img\\brick\\3.png";


void initStars(GameState* game)
{
    for(int i = 0; i < NUM_BIRDS; i++)
    {
        game->birds[i].baseX = 320 + rand()%38400;
        game->birds[i].baseY = rand()%480;
        game->birds[i].mode = rand()%2;
        game->birds[i].phase = 2*3.14*(rand()%360)/360.0f;
    }
}

void init(GameState *game)
{
    initStars(game);
    game->man.x = 200;
    game->man.y = 200;
    game->man.dy = 0;
    game->man.dx = 0;
    game->man.onLedge = 0;
    game->man.currentFrames = 0;
    game->time = 0;
    game->man.facingLeft = 1;
    game->man.slowingDown = 0;
    game->man.lives = 3;
    game->scrollX = 0;
    game->man.isDead = 0;
    game->deathCountdown = -1;
}

void load_whitebird(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(WHITE_BIRD_FILE);
    if(Surpic == NULL){cout << "Cannot find BIRD picture!" << "\n";SDL_Quit();return;}
    game->bird = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void load_man(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(GOKU_SPRITE_FILE);
    if(Surpic == NULL) {cout << "Cannot find MAN picture!" << "\n"; SDL_Quit(); return;}
    game->manFrames[0] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[1] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[2] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[3] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[4] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[5] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[6] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->manFrames[7] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void load_fire(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(FIRE_FILE);
    if(Surpic == NULL) {cout << "Cannot find FIRE!" << "\n";SDL_Quit(); return;}
    game->fire = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void load_heart(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(HEART_FILE);
    if(Surpic == NULL){
        cout << "Cannot find Brick!" << endl;
        SDL_Quit();
        return;
    }
    game->heart = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void load_brick(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(BRICK_FILE);
    if(Surpic == NULL){
        cout << "Cannot find Brick!" << endl;
        SDL_Quit();
        return;
    }
    game->brick = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    for(int i = 0; i < NUM_LEDGES-20; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = i*384;
        if(i == 0)
          game->ledges[i].y = 400;
        else
          game->ledges[i].y = 300+100-rand()%200;
    }

    for(int i = NUM_LEDGES-20; i < NUM_LEDGES - 10; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = 350+rand()%38400;
        if(i % 2 == 0)
          game->ledges[i].y = 200;
        else
          game->ledges[i].y = 350;
    }
}

void load_background(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(BACKGROUND_FILE);
    if(Surpic == NULL){
        cout << "Cannot find Brick!" << endl;
        SDL_Quit();
        return;
    }
    game->background = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    for(int i = 0; i < 100; i++)
    {
        game->BK[i].w = SCREEN_WIDTH;
        game->BK[i].h = SCREEN_HEIGHT;
        game->BK[i].x = i*SCREEN_WIDTH;
        game->BK[i].y = 0;
    }
}

void loadGame(GameState *game)
{
    srand((int)time(nullptr));

    init(game);

    load_whitebird(game);
    load_man(game);
    load_fire(game);
    load_heart(game);
    load_brick(game);
    load_background(game);

    //Load Fonts
    game->statusState =  STATUS_STATE_LIVES;
    game->label = NULL;
    game->label2 = NULL;
    init_status_live(game);

    //Load Sounds
    game->bgMusics = Mix_LoadWAV("sounds\\music1.wav");
    if(game->bgMusics != NULL) {
        Mix_VolumeChunk(game->bgMusics, 64);
    }
    else cout << "NOPE SOUND MUSIC" << endl;

    game->dieSound = Mix_LoadWAV("sounds\\die1.wav");
    if(game->dieSound != NULL) {
        Mix_VolumeChunk(game->dieSound, 64);
    }
    else cout << "NOPE SOUND DIE WAY" << endl;

    game->JumpSound = Mix_LoadWAV("sounds\\jump.wav");
    if(game->JumpSound != NULL) {
        Mix_VolumeChunk(game->JumpSound, 64);
    }
    else cout << "NOPE SOUND JUMP" << endl;

    game->landSound = Mix_LoadWAV("sounds\\land.wav");
    if(game->landSound != NULL) {
        Mix_VolumeChunk(game->landSound, 64);
    }
    else cout << "NOPE SOUND LAND" << endl;
}
