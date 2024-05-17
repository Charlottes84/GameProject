#include <bits/stdc++.h>
#include "loadGame.h"

using namespace std;

const char* GOKU_SPRITE_FILE = "img\\Walk.png";
const char* PIG_FILE = "assets\\pig.png";
const char* PRINCESS_FILE = "img\\princess.png";
const char* FIRE_FILE = "fire.png";
const char* WHITE_BIRD_FILE = "whitebird.png";
const char* BOT_VER2_FILE = "assets\\bot2.png";
const char* HEART_FILE = "heart.png";
const char* BACKGROUND_FILE = "assets\\img\\background\\background1.png";
const char* BRICK_FILE = "assets\\img\\brick\\2.png";
const char* BULLET_SPHERE_FILE = "assets\\img\\bullet\\sphere.png";
const char* BULLET_LASER_FILE = "assets\\img\\bullet\\laser.png";
const char* BULLET_HEART_FILE = "assets\\img\\bullet\\heart.png";


void initStars(GameState *game)
{
    for(int i = 0; i < NUM_BIRDS; i++)
    {
        game->birds[i].baseX = 320 + rand()%LIMIT_X;
        game->birds[i].baseY = (rand()%LIMIT_Y > 100) ? rand()%LIMIT_Y : 100;
        game->birds[i].mode = rand()%2;
        game->birds[i].phase = 2*3.14*(rand()%360)/360.0f;
    }
}

void initBots(GameState *game)
{
    for(int i = 0; i < NUM_BIRDS; i++)
    {
        game->bots[i].baseX = 320 + rand()%LIMIT_X;
        game->bots[i].baseY = (rand()%LIMIT_Y > 100) ? rand()%LIMIT_Y : 100;
        game->bots[i].mode = rand()%2;
        game->bots[i].phase = 2*3.14*(rand()%360)/360.0f;
    }
}

//NOTE
void initPrincess(GameState *game)
{
    game->prin.i = 1;
    game->ledges[game->prin.i].x = game->prin.i*384;
    game->ledges[game->prin.i].y = 300;

    game->prin.baseX = game->ledges[game->prin.i].x + 100;
    game->prin.baseY = game->ledges[game->prin.i].y - 80;
    game->prin.phase = 3.14;
}

void init(GameState *game)
{
    initStars(game);
    initBots(game);

    game->time = 0;
    game->check = false;
    game->scrollX = 0;
    game->deathCountdown = -1;
    game->check_win = false;

    game->pi.currentFrames = 0;
    game->pi.time = 0;

    game->prin.currentFrames = 0;
    game->prin.facingleft = 1;

    game->mouse.isMouse = false;
    game->mouse.isClick_start = false;
    game->mouse.isMouse_control = false;
    game->mouse.isClick_control = false;
    game->mouse.isClick_back = false;
    game->mouse.isMouse_back = false;

    game->man.x = 150;
    game->man.y = 150;
    game->man.dy = 0;
    game->man.dx = 0;
    game->man.onLedge = 0;
    game->man.currentFrames = 0;
    game->man.facingLeft = 1;
    game->man.slowingDown = 0;
    game->man.lives = 3;
    game->man.isDead = 0;

    game->bullet.x = -30;
    game->bullet.y = -30;
    game->bullet.time = 0;
    game->bullet.is_move = false;
    game->bullet.ready = true;
    game->bullet.cnt = 0;
    game->bullet.aim = false;
    game->bullet.collision = 0;

    game->bullet_laser.x = 0;
    game->bullet_laser.y = 0;
    game->bullet_laser.time = 0;
    game->bullet_laser.is_move = false;
    game->bullet_laser.ready = true;
    game->bullet_laser.cnt = 0;
    game->bullet_laser.aim = false;
    game->bullet_laser.collision = 0;

    game->bullet_heart.x = -150;
    game->bullet_heart.y = -150;
    game->bullet_heart.time = 0;
    game->bullet_heart.is_move = false;
    game->bullet_heart.ready = true;
    game->bullet_heart.cnt = 0;
    game->bullet_heart.aim = false;
    game->bullet_heart.collision = 0;
}

void load_princess(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(PRINCESS_FILE);
    if(Surpic == NULL) {cout << "Can't find princess!" << "\n"; SDL_Quit(); return;}
    game->princess[0] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->princess[1] = game->princess[0];
    game->princess[2] = game->princess[0];
    game->princess[3] = game->princess[0];
    game->princess[4] = game->princess[0];
    game->princess[5] = game->princess[0];
    SDL_FreeSurface(Surpic);
}

void load_pig(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(PIG_FILE);
    if(Surpic == NULL) {cout << "Can't find PIG!" << "\n"; SDL_Quit(); return;}
    game->pig[0] = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    game->pig[1] = game->pig[0];
    game->pig[2] = game->pig[0];
    game->pig[3] = game->pig[0];
    game->pig[4] = game->pig[0];
    game->pig[5] = game->pig[0];
    game->pig[6] = game->pig[0];
    SDL_FreeSurface(Surpic);
}

void load_whitebird(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(WHITE_BIRD_FILE);
    if(Surpic == NULL){cout << "Cannot find BIRD picture!" << "\n";SDL_Quit();return;}
    game->bird = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(BOT_VER2_FILE);
    if(Surpic == NULL) {cout << "Can't find BOT!" << "\n"; SDL_Quit(); return;}
    game->bot = SDL_CreateTextureFromSurface(game->renderer, Surpic);
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
    if(Surpic == NULL){ cout << "Cannot find Brick!" << endl; SDL_Quit(); return; }
    game->heart = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void load_brick(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(BRICK_FILE);
    if(Surpic == NULL){ cout << "Cannot find Brick!" << endl; SDL_Quit(); return; }
    game->brick = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    for(int i = 0; i < NUM_LEDGES-20; i++)
    {
        game->ledges[i].w = LEDGES_W;
        game->ledges[i].h = LEDGES_H;
        game->ledges[i].x = i*384;
        if(i == 0)
          game->ledges[i].y = 400;
        else
          game->ledges[i].y = 400-rand()%200;
    }
}

void load_background(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(BACKGROUND_FILE);
    if(Surpic == NULL){ cout << "Cannot find Brick!" << endl;  SDL_Quit(); return;}
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

void load_bullet(GameState *game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(BULLET_SPHERE_FILE);
    if(Surpic == NULL){ cout << "Cannot find SPHERE!" << endl; SDL_Quit(); return;}
    game->sphere = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(BULLET_LASER_FILE);
    if(Surpic == NULL) {cout << "Cannot find LASER!" << "\n"; SDL_Quit(); return;}
    game->laser = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(BULLET_HEART_FILE);
    if(Surpic == NULL) {cout << "Can't find HEART!" << "\n"; SDL_Quit(); return;}
    game->bul_heart = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
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
    load_bullet(game);
    load_princess(game);
    load_pig(game);
    initPrincess(game);

    //Load Fonts
    game->statusState =  STATUS_STATE_MENU;
    game->label = NULL;
    game->label2 = NULL;
    init_game_menu(game);

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
