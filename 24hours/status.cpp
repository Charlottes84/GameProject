#include <bits/stdc++.h>
#include "status.h"

const char *BGMENU_FILE = "assets\\img\\menu\\bk_menu4.png";
const char *START1 = "assets\\img\\menu\\Start_Button.png";
const char *START2 = "assets\\img\\menu\\Start_col_Button.png";
const char *CONTROL1 = "assets\\img\\menu\\Controls_Button.png";
const char *CONTROL2 = "assets\\img\\menu\\Controls_col_Button.png";
const char *BACK1 = "assets\\img\\menu\\Back_Button.png";
const char *BACK2 = "assets\\img\\menu\\Back_col_Button.png";
const char *QUIT1 = "assets\\img\\menu\\Quit_Button.png";
const char *QUIT2 = "assets\\img\\menu\\Quit_col_Button.png";
const char *CONTROL = "assets\\img\\menu\\control.png";
const char *LIVES = "assets\\img\\menu\\uhave.png";
const char *WIN = "assets\\img\\menu\\uwin.png";
const char *GAMEOVER = "assets\\img\\menu\\gameover.png";

#define START_BAR_W 600
#define START_BAR_H 200

using namespace std;

void init_status_live(GameState *game)
{
//    game->font = TTF_OpenFont("fonts\\Crazy-Pixel.ttf", 40);
//    if(game->font == NULL) { printf("Font loading failed: %s\n", TTF_GetError()); }

    char str[128] = "";
    sprintf(str, "x %d%", (int)game->man.lives);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, str, white, 800);
    game->labelW = TextSurface->w;
    game->labelH = TextSurface->h;
    if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }
    game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(TextSurface == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }
    SDL_FreeSurface(TextSurface);

    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(LIVES);
    if(Surpic == NULL) {cout << "Can't find UHAVE!" << "\n"; SDL_Quit(); return;}
    game->lives_bg = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

}
void draw_status_lives(GameState *game)
{
    SDL_Renderer* Renderer = game->renderer;

    SDL_Rect rect_bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, game->lives_bg, NULL, &rect_bg);

    SDL_Rect rect = {SCREEN_WIDTH/2 - 170, SCREEN_HEIGHT/2 - 90, game->labelW + 150, game->labelH + 150};
    SDL_RenderCopy(Renderer, game->label, NULL, &rect);

    SDL_Rect Rheart = {SCREEN_WIDTH/2 - 130, SCREEN_HEIGHT/2 - 240, 500, 500};
    SDL_RenderCopy(Renderer, game->heart, NULL, &Rheart);


    SDL_RenderPresent(Renderer);
}

void shutdown_status_lives(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;

    SDL_DestroyTexture(game->label2);
    game->label2 = NULL;

    SDL_DestroyTexture(game->lives_bg);
    game->lives_bg = NULL;
}

void init_game_over(GameState *game)
{
   SDL_Color white = {255, 255, 255, 255};

   SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, "GAME OVER", white, 800);
   game->labelW = TextSurface->w;
   game->labelH = TextSurface->h;
   if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }
   game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
   if(game->label == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }
   SDL_FreeSurface(TextSurface);

    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(GAMEOVER);
    if(Surpic == NULL) {cout << "Can't find GAMEOVER!" << "\n"; SDL_Quit(); return;}
    game->gameover = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void draw_game_over(GameState *game)
{
    SDL_Rect rect_bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(game->renderer, game->gameover, NULL, &rect_bg);
}

void shutdown_game_over(GameState* game)
{
    SDL_DestroyTexture(game->gameover);
    game->gameover = NULL;
}

void init_game_win(GameState* game)
{
    SDL_Surface *Surpic = NULL;
    Surpic = IMG_Load(WIN);
    if(Surpic == NULL) {cout << "Can't find GAMEOVER!" << "\n"; SDL_Quit(); return;}
    game->win = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void draw_game_win(GameState* game)
{
    SDL_Rect rect_bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(game->renderer, game->win, NULL, &rect_bg);
}

void shutdown_game_win(GameState* game)
{
    SDL_DestroyTexture(game->win);
    game->win = NULL;
}

void init_game_progressbar(GameState *game)
{
    char str[128] = "";
    sprintf(str, "%d% %", (int)(game->man.x/(FINISH/100)));


    SDL_Color red = {95, 185, 213};
    SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, str, red, 800);
    game->labelW = TextSurface->w;
    game->labelH = TextSurface->h;
    if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }

    game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(game->label == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }

    SDL_FreeSurface(TextSurface);
}

void draw_game_progressbar(GameState *game)
{
    SDL_Renderer* renderer = game->renderer;
    SDL_Rect RectText = {(250 + 380/2 + 50), -15, game->labelW, game->labelH};
    SDL_RenderCopy(renderer, game->label, NULL, &RectText);
}

void shutdown_game_progressbar(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}

void init_status_crip(GameState *game)
{

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, "Xin chao Cong chua cua anh, anh xin loi vi da lam cham tre deadline. Tai co mot chut truc trac nen anh da hoan thanh muon a, mong cong chua cua anh tha loi cho anh. May ngay qua anh co gang de lam lai game, tai vi hom nay gap em nen anh da co gang hoan thien nhanh nhat co the, nhung ma van chua xong a, van con may loi nho nho can phai sua va them vao a. Khong sao ca anh nghi game hom nay cung hay y a, mong em thich no. ANH YEU EM BABEEEE ^^", white, 700);
    game->labelW = TextSurface->w;
    game->labelH = TextSurface->h;
    if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }
    game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(TextSurface == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }
    SDL_FreeSurface(TextSurface);
}
void draw_status_crip(GameState *game)
{
    SDL_Renderer* Renderer = game->renderer;

    //Text - x3
    SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 255);
    SDL_RenderClear(Renderer);

    SDL_Rect rect = {380, 200, game->labelW, game->labelH};
    SDL_RenderCopy(Renderer, game->label, NULL, &rect);

    SDL_RenderPresent(Renderer);
}

void shutdown_status_crip(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}

void init_game_menu(GameState *game)
{
    game->font = TTF_OpenFont("fonts\\Crazy-Pixel.ttf", 40);
    if(game->font == NULL) { printf("Font loading failed: %s\n", TTF_GetError()); }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, "Menu", white, 800);
    game->labelW = TextSurface->w;
    game->labelH = TextSurface->h;
    if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }
    game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(TextSurface == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }
    SDL_FreeSurface(TextSurface);

    SDL_Surface *Surpic = NULL;

    Surpic = IMG_Load(BGMENU_FILE);
    if(Surpic == NULL) {cout << "Can't find BGMENU!" << "\n"; SDL_Quit(); return;}
    game->bkmenu = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(START1);
    if(Surpic == NULL) {cout << "Can't find START1" << "\n"; SDL_Quit(); return;}
    game->st1 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    game->mouse.rectW = Surpic->w/2.4;
    game->mouse.rectH = Surpic->h/2.4;
    game->mouse.rectX = SCREEN_WIDTH/2 - START_BAR_W/6 - 30;
    game->mouse.rectY = SCREEN_HEIGHT/2 - 15;

    Surpic = IMG_Load(START2);
    if(Surpic == NULL) {cout << "Can't find START2" << "\n"; SDL_Quit(); return;}
    game->st2 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(CONTROL1);
    if(Surpic == NULL) {cout << "Can't find CONTROL1" << "\n"; SDL_Quit(); return;}
    game->ctr1 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    game->menu.control_w = Surpic->w/2.4;
    game->menu.control_h = Surpic->h/2.4;
    game->menu.control_x = SCREEN_WIDTH/2 - START_BAR_W/6 - 30;
    game->menu.control_y = game->mouse.rectY + 100;

    Surpic = IMG_Load(CONTROL2);
    if(Surpic == NULL) {cout << "Can't find CONTROL2" << "\n"; SDL_Quit(); return;}
    game->ctr2 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(QUIT1);
    if(Surpic == NULL) {cout << "Can't find QUIT1" << "\n"; SDL_Quit(); return;}
    game->qu1 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    game->menu.quit_x = SCREEN_WIDTH/2 - START_BAR_W/6 - 30;
    game->menu.quit_y = game->menu.control_y + 100;
    game->menu.quit_w = Surpic->w/2.4;
    game->menu.quit_h = Surpic->h/2.4;

    Surpic = IMG_Load(QUIT2);
    if(Surpic == NULL) {cout << "Can't find QUIT2" << "\n"; SDL_Quit(); return;}
    game->qu2 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void draw_game_menu(GameState *game)
{
    SDL_Renderer *Renderer = game->renderer;

    //text
    SDL_Rect rect = {20, 20, game->labelW, game->labelH};
    SDL_RenderCopy(Renderer, game->label, NULL, &rect);

    //background
    SDL_Rect bgmenu_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, game->bkmenu, NULL, &bgmenu_rect);

    //start
    SDL_Rect start1_rect = {game->mouse.rectX, game->mouse.rectY, game->mouse.rectW, game->mouse.rectH};
    if(game->mouse.isMouse == false) {SDL_RenderCopy(Renderer, game->st1, NULL, &start1_rect);}
    else {SDL_RenderCopy(Renderer, game->st2, NULL, &start1_rect);}

    //controls
    SDL_Rect control_rect = {game->menu.control_x, game->menu.control_y, game->menu.control_w, game->menu.control_h};
    if(game->mouse.isMouse_control == false) {SDL_RenderCopy(Renderer, game->ctr1, NULL, &control_rect);}
    else {SDL_RenderCopy(Renderer, game->ctr2, NULL, &control_rect);}

    //quit
    SDL_Rect quit_rect = {game->menu.quit_x, game->menu.quit_y, game->menu.quit_w, game->menu.quit_h};
    if(game->mouse.isMouse_quit == false) {SDL_RenderCopy(Renderer, game->qu1, NULL, &quit_rect);}
    else {SDL_RenderCopy(Renderer, game->qu2, NULL, &quit_rect);}
}

void shutdown_game_menu(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;

    SDL_DestroyTexture(game->bkmenu);
    game->bkmenu = NULL;

    SDL_DestroyTexture(game->st1);
    game->st1 = NULL;
    SDL_DestroyTexture(game->st2);
    game->st2 = NULL;

    SDL_DestroyTexture(game->ctr1);
    game->ctr1 = NULL;
    SDL_DestroyTexture(game->ctr2);
    game->ctr2 = NULL;

    SDL_DestroyTexture(game->qu1);
    SDL_DestroyTexture(game->qu2);
    game->qu1 = NULL;
    game->qu2 = NULL;
}


void init_game_control(GameState *game)
{
    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, "Control", white, 800);
    game->labelW = TextSurface->w;
    game->labelH = TextSurface->h;
    if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }
    game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(TextSurface == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }
    SDL_FreeSurface(TextSurface);

    SDL_Surface *Surpic = NULL;

    Surpic = IMG_Load(BACK1);
    if(Surpic == NULL) {cout << "Can't find BACK1!" << "\n"; SDL_Quit(); return;}
    game->ba1 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    game->menu.back_x = 20;
    game->menu.back_y = 10;
    game->menu.back_w = Surpic->w/4;
    game->menu.back_h = Surpic->h/4;

    Surpic = IMG_Load(BACK2);
    if(Surpic == NULL) {cout << "Can't find BACK2!" << "\n"; SDL_Quit(); return;}
    game->ba2 = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);

    Surpic = IMG_Load(CONTROL);
    if(Surpic == NULL) {cout << "Can't find CONTROL_BG!" << "\n"; SDL_Quit(); return;}
    game->bg_control = SDL_CreateTextureFromSurface(game->renderer, Surpic);
    SDL_FreeSurface(Surpic);
}

void draw_game_control(GameState *game)
{
    SDL_Renderer *Renderer = game->renderer;
    SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 255);
    SDL_RenderClear(Renderer);

    //text
    SDL_Rect rect = {20, 20, game->labelW, game->labelH};
    SDL_RenderCopy(Renderer, game->label, NULL, &rect);

    //bg
    SDL_Rect rect_bg = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(Renderer, game->bg_control, NULL, &rect_bg);

    //BACK
    SDL_Rect back_rect = {game->menu.back_x, game->menu.back_y, game->menu.back_w, game->menu.back_h};
    if(game->mouse.isMouse_back == false) {SDL_RenderCopy(Renderer, game->ba1, NULL, &back_rect);}
    else {SDL_RenderCopy(Renderer, game->ba2, NULL, &back_rect);}
}

void shutdown_game_control(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;

    SDL_DestroyTexture(game->ba1);
    SDL_DestroyTexture(game->ba2);
    game->ba1 = NULL;
    game->ba2 = NULL;
    SDL_DestroyTexture(game->bg_control);
    game->bg_control = NULL;
}
