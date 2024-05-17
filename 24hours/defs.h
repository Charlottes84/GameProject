#ifndef _DEFS__H
#define _DEFS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 600

#define LIMIT_X 38000
#define LIMIT_Y 480
#define FINISH 16000

#define SPEED 5
#define GRAVITY 0.4f

#define MANSIZE_W 45
#define MANSIZE_H 90
#define MANSIZE_BASE_W 45
#define MANSIZE_BASE_H 90

#define NUM_LEDGES 120
#define LEDGES_W 256
#define LEDGES_H 64

#define NUM_BIRDS 100
#define BIRD_SIZE 64
#define BOT_SIZE 32

#define FIRE_W 38
#define FIRE_H 83

#define STATUS_STATE_MENU       4
#define STATUS_STATE_CONTROL    5
#define STATUS_STATE_LIVES      0
#define STATUS_STATE_GAME       1
#define STATUS_STATE_GAMEOVER   2
#define STATUS_STATE_WINGAME    3

struct Bird
{
    int x, y, baseX, baseY, mode;
    bool alive;
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

struct Bullet
{
    int x, y;

    int time, cnt;
    int collision;

    bool is_move;
    bool ready;
    bool aim;
};

struct Mouse
{
    int x, y;
    bool isMouse;
    bool isMouse_control;
    bool isMouse_back;
    bool isMouse_quit;

    bool isClick_start;
    bool isClick_control;
    bool isClick_back;
    bool isClick_quit;

    int rectX, rectY, rectW, rectH;
};

struct Menu
{
    int control_x, control_y, control_w, control_h;
    int back_x, back_y, back_w, back_h;
    int quit_x, quit_y, quit_w, quit_h;
};

struct Princess
{
    int x, y, baseX, baseY, mode;
    int i;
    int currentFrames;
    int facingleft;
    float phase;
};

struct Pig
{
    int x, y, baseX, baseY, mode;
    int time;
    int currentFrames;
    int facingleft;
    float phase;
};

struct GameState
{
    float scrollX;
    bool check;
    bool check_win;

    //Pig
    Pig pi;

    //Princess
    Princess prin;

    //Menu
    Menu menu;

    //Mouse
    Mouse mouse;

    //Bullet
    Bullet bullet;
    Bullet bullet_laser;
    Bullet bullet_heart;

    //Player
    Character man;

    //Bird
    Bird birds[NUM_BIRDS];
    Bird bots[NUM_BIRDS];

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
    SDL_Texture *sphere;
    SDL_Texture *laser;
    SDL_Texture *princess[6];
    SDL_Texture *bot;
    SDL_Texture *bul_heart;
    SDL_Texture *pig[7];

    //Background Menu
    SDL_Texture *bkmenu;
    SDL_Texture *st1;
    SDL_Texture *st2;
    SDL_Texture *ctr1;
    SDL_Texture *ctr2;
    SDL_Texture *ba1;
    SDL_Texture *ba2;
    SDL_Texture *qu1;
    SDL_Texture *qu2;
    SDL_Texture *bg_control;
    SDL_Texture *lives_bg;
    SDL_Texture *gameover;
    SDL_Texture *win;

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
    Mix_Chunk *collect, *hover, *bullet_mc;

    //Joystick
    SDL_Joystick *joystick;

    //Renderer
    SDL_Renderer *renderer;
};

#endif // _DEFS__H
