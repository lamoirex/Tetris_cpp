#include "game.h"
#ifndef LINUX
#include <windows.h>
#endif

//int main(void) 
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // ------ Vars ------
    IO mIO;
    int mScreenHeight = mIO.getScreenHeight();

    // Pieces
    Pieces tetrisBlocks;

    // Board
    Board mBoard(&tetrisBlocks, mScreenHeight);

    // Game
    Game mGame(&mBoard, &tetrisBlocks, &mIO, mScreenHeight);

    // Get the actual clock milliseconds (SDL)
    unsigned long mTime1 = SDL_GetTicks();
    
    // ------ Main Loop ------
    while (!mIO.isKeyDown(SDLK_ESCAPE))
    {
        // ------ Draw ------
        mIO.clearScreen(); // Clear screen
        mGame.drawScene(); // Draw staff
        mIO.updateScreen(); // Put the graphic context in the screen
        
        // ------ Input ------
        int mKey = mIO.pollKey();

        switch(mKey)
        {
            case(SDLK_RIGHT):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                    mGame.mPosX++;
                break;
            }
            case(SDLK_LEFT):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                    mGame.mPosX--;
                break;
            }
            case(SDLK_DOWN):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
                    mGame.mPosY++;
                break;
            }
            case(SDLK_x):
            {
                // Check the collision from up to down
                while(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) {
                    mGame.mPosY++;
                }

                mBoard.storePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

                mBoard.deletePossibleLines();

                if(mBoard.isGameOver())
                {
                    mIO.getKey();
                    exit(0);
                }

                mGame.createNewPiece();

                break;
            }
            case(SDLK_z):
            {
                if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
                    mGame.mRotation = (mGame.mRotation + 1) % 4; 
                break;                
            }
        }
        // ------ Vertical movement ------

        unsigned long mTime2 = SDL_GetTicks();

        if((mTime2 - mTime1) > WAIT_TIME)
        {
            if(mBoard.isPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
            {
                mGame.mPosY++;
            }
            else
            {
                mBoard.storePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                
                mBoard.deletePossibleLines();

                if(mBoard.isGameOver())
                {
                    mIO.getKey();
                    exit(0);
                }

                mGame.createNewPiece();
            }

            mTime1 = SDL_GetTicks();
        }

    }

    return 0;
}
