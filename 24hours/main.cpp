#include <bits/stdc++.h>
#include "collisionGame.h"

using namespace std;

int main(int agrc, char* agrv[])
{
    //Init Window + Renderer
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    GameState gameState;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);
    gameState.joystick = SDL_JoystickOpen(0);


    //Create window
    window = SDL_CreateWindow("Game window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT, 0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |SDL_RENDERER_PRESENTVSYNC);

    TTF_Init();

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);

    //Game
    gameState.renderer = renderer;
    loadGame(&gameState);

    bool done = false;
    cout << "update 5" << endl;

    while(!done)
    {
        done = process(renderer, &gameState, window);
        Move(&gameState);
        collisionDetect(&gameState);
        doRender(renderer, &gameState);

        SDL_Delay(10);
    }
    cout << gameState.bullet.collision;

    //Destroy Texture
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(gameState.bird);
    SDL_DestroyTexture(gameState.brick);
    SDL_DestroyTexture(gameState.manFrames[0]);
    SDL_DestroyTexture(gameState.manFrames[1]);
    SDL_DestroyTexture(gameState.manFrames[2]);
    SDL_DestroyTexture(gameState.manFrames[3]);
    SDL_DestroyTexture(gameState.manFrames[4]);
    SDL_DestroyTexture(gameState.manFrames[5]);
    SDL_DestroyTexture(gameState.manFrames[6]);
    SDL_DestroyTexture(gameState.manFrames[7]);

    //Fonts
    if(gameState.label != NULL)
        SDL_DestroyTexture(gameState.label);
    if(gameState.label2 != NULL)
        SDL_DestroyTexture(gameState.label2);
    TTF_CloseFont(gameState.font);
    TTF_Quit();

    //Sounds
    Mix_FreeChunk(gameState.bgMusics);
    Mix_FreeChunk(gameState.dieSound);
    Mix_FreeChunk(gameState.JumpSound);
    Mix_FreeChunk(gameState.landSound);

    //Joystick
    if(gameState.joystick)
    SDL_JoystickClose(gameState.joystick);

    SDL_Quit();
    return 0;
}
