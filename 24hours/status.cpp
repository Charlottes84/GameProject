#include <bits/stdc++.h>
#include "status.h"

using namespace std;

void init_status_live(GameState *game)
{
    game->font = TTF_OpenFont("fonts\\Crazy-Pixel.ttf", 40);
    if(game->font == NULL) { printf("Font loading failed: %s\n", TTF_GetError()); }

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


    SDL_Color lightBlue = { 128, 192, 255, 255 };
    TextSurface = TTF_RenderText_Blended(game->font, "Get to the end alive!", lightBlue);
    game->label2W = TextSurface->w;
    game->label2H = TextSurface->h;
    game->label2 = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(TextSurface == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }
    SDL_FreeSurface(TextSurface);

}
void draw_status_lives(GameState *game)
{
    SDL_Renderer* Renderer = game->renderer;

    //Text - x3
    SDL_SetRenderDrawColor(Renderer, 30, 30, 30, 255);
    SDL_RenderClear(Renderer);

    SDL_Rect rect = {20, 20, game->labelW, game->labelH};
    SDL_RenderCopy(Renderer, game->label, NULL, &rect);
    //Text - Get to the end alive
    SDL_Rect rect2 = {380 - 90, 100, game->label2W, game->label2H};
    //SDL_RenderCopy(Renderer, game->label2, NULL, &rect2);

    //Img Man
    SDL_Rect Rheart = {160, 305, 300, 300};
    SDL_RenderCopy(Renderer, game->heart, NULL, &Rheart);


    SDL_RenderPresent(Renderer);
}

void shutdown_status_lives(GameState *game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;

    SDL_DestroyTexture(game->label2);
    game->label2 = NULL;
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
}

void draw_game_over(GameState *game)
{
    SDL_Renderer* renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect RectText = {320 - game->labelW/2, 240 - game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &RectText);
}

void shutdown_game_over(GameState* game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}

void init_game_win(GameState* game)
{
    SDL_Color white = {255, 255, 255};
    SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(game->font, "YOU WIN!", white, 800);
    game->labelW = TextSurface->w;
    game->labelH = TextSurface->h;
    if(TextSurface == NULL) { printf("Surface creation failed: %s\n", TTF_GetError()); }

    game->label = SDL_CreateTextureFromSurface(game->renderer, TextSurface);
    if(game->label == NULL) { printf("Texture creation failed: %s\n", TTF_GetError()); }

    SDL_FreeSurface(TextSurface);
}

void draw_game_win(GameState* game)
{
    SDL_Renderer* renderer = game->renderer;
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect RectText = {320 - game->labelW/2, 240 - game->labelH/2, game->labelW, game->labelH };
    SDL_RenderCopy(renderer, game->label, NULL, &RectText);
}

void shutdown_game_win(GameState* game)
{
    SDL_DestroyTexture(game->label);
    game->label = NULL;
}

void init_game_progressbar(GameState *game)
{
    char str[128] = "";
    sprintf(str, "%d% %", (int)(game->man.x/3800));

    SDL_Color red = {255, 0, 0};
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
    SDL_Rect RectText = {(250 + 380/2), 32, game->labelW, game->labelH };
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
