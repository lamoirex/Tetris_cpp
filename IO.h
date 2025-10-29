#ifndef _IO_
#define _IO_

// ------ Includes ------

#ifndef LINUX
#include "SDL/include/SDL2/SDL.h"
#else
#include <SDL/SDL.h>
#endif
#pragma comment (lib, "SDL/lib/SDL.lib")
#pragma comment (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

// ------ Enums ------

enum color {BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX}; // Colors

// ------ IO ------
class IO
{
    public:

    IO();

    void drawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
    void clearScreen();
    int getScreenHeight();
    int initGraph();
    int pollKey();
    int getKey();
    int isKeyDown(int pKey);
    void updateScreen();
    
    private:
    static SDL_Surface *mScreen;
    static SDL_Window *mWindow;  // Добавьте эту строку
    static Uint32 mColors[COLOR_MAX];
};

#endif