#ifndef _BOARD_
#define _BOARD_
// ------ Includes ------

#include "pieces.h"
#include "blocks.h"

// ------ Defines ------

#define BOARD_LINE_WIDTH 6 // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 16 // Width and Height of each block of a piece
#define BOARD_POSITION 320 // Center postiion of the board from the left of the screen
#define BOARD_WIDTH 10 // Board width in blocks
#define BOARD_HEIGHT 20 // Board height in blocks
#define MIN_VERTICAL_MARGIN 20 // Minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN 20 // Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5 // Number of horizontal and vertical blocks of a matrix piece

// ------ Board ------
class Board
{
    public:

    Board(Pieces *pPieces, int pScreenHeight);

    int getXPosInPixels(int pPos);
    int getYPosInPixels(int pPos);
    bool isFreeBlock(int pX, int pY);
    bool isPossibleMovement(int pX, int pY, int pPiece, int pRotation);
    void storePiece(int pX, int pY, int pPiece, int pRotation);
    void deletePossibleLines();
    bool isGameOver();

    private:

    enum { POS_FREE, POS_FILLED };  // POS_FREE = free position of the board; POS_FILLED = filled position of the board
    int mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces
    Pieces *tetrisBlocks;
    int mScreenHeight;

    void initBoard();
    void deleteLine(int pY);
};   

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
            if (tetrisBlocks->getBlockType(pPiece, pRotation, j2, i2) != 0)
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
    // Checks collision with pieces already stored in the board or the board limits
    for(int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++)
    {
        for(int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++)
        {
            // Check if the piece is outside the limits of the board
            if( i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT -1)
            {
                if (tetrisBlocks->getBlockType(pPiece, pRotation, j2, i2) != 0)
                    return 0;
            }
            // Check if the piece have collisioned with a block already stored in the map
            if(j1 >= 0)
            {
                if ((tetrisBlocks->getBlockType(pPiece, pRotation, j2, i2) != 0) && (!isFreeBlock(i1,j1)) )
                    return false;
            }
        }
    }
    // No collision
    return true;
};
#endif