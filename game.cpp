// ------ Includes -----

#include "game.h"
#include <iostream>

// ------ Class: Game -----

Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight) 
{
	mScreenHeight = pScreenHeight;

	// Get the pointer to the Board and Pieces classes
	mBoard = pBoard;
	tetrisBlocks = pPieces;
	mIO = pIO;

	// Game initialization
	initGame ();
}

/*Get a random int between to integers*/

int Game::getRand(int pA, int pB)
{
    return rand() % (pB - pA + 1) + pA;
};

/*Initialise parameters of the game*/
void Game::initGame()
{
    // Init random numbers
    srand((unsigned int)time(NULL));

    // First piece
    mPiece = getRand(0,6);
    mRotation = getRand(0,3);
    mPosX = (BOARD_WIDTH / 2) + tetrisBlocks->getXInitialPosition(mPiece, mRotation);
    mPosY = tetrisBlocks->getYInitialPosition(mPiece, mRotation);

    // Next piece
    mNextPiece = getRand(0,6);
    mNextRotation = getRand(0,3);
    mNextPosX = BOARD_WIDTH + 5;
    mNextPosY = 5;
};

/*Create a random piece*/
void Game::createNewPiece()
{
    // The new piece
    mPiece = mNextPiece;
    mRotation = mNextRotation;
    mPosX = (BOARD_WIDTH / 2) + tetrisBlocks->getXInitialPosition(mPiece, mRotation);
    mPosY = tetrisBlocks->getYInitialPosition(mPiece, mRotation);

    // Random next piece
    mNextPiece = getRand(0,6);
    mNextRotation = getRand(0,3);
    
};

/*Draw piece*/
void Game::drawPiece(int pX, int pY, int pPiece, int pRotation)
{
    color mColor;

    int mPixelsX = mBoard->getXPosInPixels(pX);
    int mPixelsY = mBoard->getYPosInPixels(pY);

    for (int y = 0; y < PIECE_BLOCKS; y++)  // y - вертикальная координата в матрице фигуры
    {
        for (int x = 0; x < PIECE_BLOCKS; x++)  // x - горизонтальная координата в матрице фигуры
        {
            // Получаем тип блока
            int blockType = tetrisBlocks->getBlockType(pPiece, pRotation, x, y);
            
            if (blockType == 0) continue; // Пропускаем пустые блоки

            // Выбираем цвет
            switch (blockType)
            {
            case 1: mColor = GREEN; break; // Обычный блок
            case 2: mColor = BLUE; break;  // Центральный блок (pivot)
            }

            // Рисуем блок
            // x - горизонтальное смещение, y - вертикальное смещение
            mIO->drawRectangle(mPixelsX + x * BLOCK_SIZE, 
                              mPixelsY + y * BLOCK_SIZE,
                              mPixelsX + x * BLOCK_SIZE + BLOCK_SIZE - 1,
                              mPixelsY + y * BLOCK_SIZE + BLOCK_SIZE - 1,
                              mColor);
        }
    }
}
/*Draw the two lines that delimit the board*/
void Game::drawBoard()
{
    // Calculate the limits of the board in pixels
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    // Check that the vertical margin is not to small
    // assert (mY > MIN_VERTICAL_MARGIN);

    // Rectangles that delimits the board
    mIO->drawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);
    mIO->drawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

    // Check that the horizontal margin is not to small
    // assert (mX1 > MIN_HORIZONTAL_MARGIN);

    // Drawing the blocks that are already stored in the board
    mX1 += 1;
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        for(int j = 0; j < BOARD_HEIGHT; j++)
        {
            // Check if the block is filled, if so, draw it
            if (!mBoard->isFreeBlock(i,j))
                mIO->drawRectangle(mX1 + i*BLOCK_SIZE, mY + j*BLOCK_SIZE,
                                    (mX1 + i*BLOCK_SIZE) + BLOCK_SIZE - 1,
                                     (mY + j*BLOCK_SIZE) + BLOCK_SIZE - 1,
                                      BLUE);
        }
    }
};

/*Draw all the objects of the scene*/
void Game::drawScene()
{
    drawBoard();
    drawPiece(mPosX, mPosY, mPiece, mRotation);
    drawPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
    
};