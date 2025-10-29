// ------ Includes ------

#include "Board.h"

// ------ Class: Board ------
Board::Board (Pieces *pPieces, int pScreenHeight)
{
	// Get the screen height
	mScreenHeight = pScreenHeight;

	// Get the pointer to the pieces class
	tetrisBlocks = pPieces;

	//Init the board blocks with free positions
	initBoard();
}

/*Init the board blocks with free positions*/
void Board::initBoard()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            mBoard[i][j] = POS_FREE;
};

/*Store a piece in the board by filling the blocks*/
void Board::storePiece(int pX, int pY, int pPiece, int pRotation) 
{
    for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
    {
        for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
        {
            // Store only the blocks of the piece that are not holes
            if (tetrisBlocks->getBlockType(pPiece, pRotation, i2, j2) != 0) // Поменяйте i2, j2 местами
                mBoard[i1][j1] = POS_FILLED;
        }
    }
};

/*Check if the game is over because of a piece achieving the upper position*/
bool Board::isGameOver()
{
    //If the first line has blocks, then, game over
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        if (mBoard[i][0] == POS_FILLED) return true;
    }
    return false;
}

/*Delete a line of the board by moving all above lines down*/
void Board::deleteLine (int pY)
{
    // Moves all the upper lines one row down
    for (int j = pY; j > 0; j--)
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            mBoard[i][j] = mBoard[i][j-1];
        }
    }
};

/*Delete all the lines that should be removed*/
void Board::deletePossibleLines()
{
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int i = 0;
        while( i < BOARD_WIDTH)
        {
            if (mBoard[i][j] != POS_FILLED) break;
            i++;
        }
        if (i == BOARD_WIDTH) deleteLine(j);
    }
};

/*Returns 1 (true) if this block of the board is empty, 0 if it is filled*/
bool Board::isFreeBlock(int pX, int pY)
{
    if (mBoard[pX][pY] == POS_FREE) return true; else return false;
};

/*Returns the horizontal position (in pixels) of the block given like parameter*/
int Board::getXPosInPixels(int pPos)
{
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
};

/*Returns the vertical position (in pixels) of the block given like parameter*/
int Board::getYPosInPixels(int pPos)
{
    return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
};

/*Check if the piece can be stored at this position without any collision
Returns true if the movement is possible, false if it not possible*/
bool Board::isPossibleMovement(int pX, int pY, int pPiece, int pRotation) 
{
    for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
    {
        for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
        {
            if( i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT -1)
            {
                if (tetrisBlocks->getBlockType(pPiece, pRotation, i2, j2) != 0) // Поменяйте местами
                    return 0;
            }
            if(j1 >= 0)
            {
                if ((tetrisBlocks->getBlockType(pPiece, pRotation, i2, j2) != 0) && (!isFreeBlock(i1,j1)) ) // Поменяйте местами
                    return false;
            }
        }
    }
    return true;
};