// ------ Includes -----
#include "IO.h"
#include <iostream>
#include <cstdlib>

SDL_Surface *IO::mScreen = nullptr;
SDL_Window *IO::mWindow = nullptr;

Uint32 IO::mColors[COLOR_MAX] = {
    0x000000ff, 0xff0000ff, 0x00ff00ff, 0x0000ffff,
    0x00ffffff, 0xff00ffff, 0xffff00ff, 0xffffffff
};

IO::IO()
{
    initGraph();
};

static void boxColor(SDL_Surface *screen, int x1, int y1, int x2, int y2, Uint32 color)
{
    SDL_Rect rect{ x1, y1, x2-x1+1, y2-y1+1 };
    SDL_FillRect(screen, &rect, color);
}

void IO::clearScreen()
{
    boxColor(mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[BLACK]);
};

void IO::drawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC)
{
    boxColor(mScreen, pX1, pY1, pX2, pY2, mColors[pC]);
};

int IO::getScreenHeight()
{
    return mScreen->h;
};

void IO::updateScreen()
{
    SDL_UpdateWindowSurface(mWindow);
};

int IO::pollKey()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type) {
            case SDL_KEYDOWN:
                return event.key.keysym.sym;
            case SDL_QUIT:
                exit(3);
        }
    }
    return -1;
};

int IO::getKey()
{
    SDL_Event event;
    while(true)
    {
        SDL_WaitEvent(&event);
        if(event.type == SDL_KEYDOWN)
            break;
        if(event.type == SDL_QUIT)
            exit(3);
    }
    return event.key.keysym.sym;
};

int IO::isKeyDown(int pKey)
{
    const Uint8* mKeytable;
    int mNumkeys;
    SDL_PumpEvents();
    mKeytable = SDL_GetKeyboardState(&mNumkeys);
    return mKeytable[pKey];
};

int IO::initGraph()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    mWindow = SDL_CreateWindow("Tetris", 
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED,
                              640, 480, 
                              SDL_WINDOW_SHOWN);
    if (!mWindow) {
        fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
        SDL_Quit();
        return 2;
    }

    mScreen = SDL_GetWindowSurface(mWindow);
    if (!mScreen) {
        fprintf(stderr, "Couldn't get window surface: %s\n", SDL_GetError());
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
        return 3;
    }

    return 0;
}

