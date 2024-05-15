#ifndef _DEFS__H
#define _DEFS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define SPEED 5
#define GRAVITY 0.4f
#define MANSIZE 100
#define MANSIZE_BASE 128
#define NUM_LEDGES 120
#define NUM_BIRDS 200
#define BIRD_SIZE 64
#define FIRE_W 38
#define FIRE_H 83

#define STATUS_STATE_LIVES      0
#define STATUS_STATE_GAME       1
#define STATUS_STATE_GAMEOVER   2
#define STATUS_STATE_WINGAME    3

struct Bird
{
    int x, y, baseX, baseY, mode;
    float phase;
};

struct Character
{
    float x, y;
    float dy, dx;

    short lives;

    int onLedge, isDead;

    int currentFrames, facingLeft, slowingDown;
};
struct Ledge
{
    int x, y, w, h;
};

struct Background
{
    int x, y, w, h;
};

struct GameState
{
    float scrollX;

    //Player
    Character man;

    //Bird
    Bird birds[NUM_BIRDS];

    //Ledges
    Ledge ledges[100];
    Background BK[100];

    //Characters
    SDL_Texture *manFrames[8];
    SDL_Texture *bird;
    SDL_Texture *brick;
    SDL_Texture *fire;
    SDL_Texture *background;
    SDL_Texture *heart;

    //Fonts
    TTF_Font *font;
    SDL_Texture *label;
    SDL_Texture *label2;
    int labelW, labelH;
    int label2W, label2H;
    int statusState;

    //Time
    int time, deathCountdown;

    //Sounds
    int musicChannel;
    Mix_Chunk *bgMusics, *JumpSound, *landSound, *dieSound;

    //Joystick
    SDL_Joystick *joystick;

    //Renderer
    SDL_Renderer *renderer;
};

#endif // _DEFS__H
