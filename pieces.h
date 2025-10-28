#ifndef _PIECES_
#define _PIECES_

// ------ Pieces ------
class Pieces
{
    public:

    int getBlockType(int pPiece, int pRotation, int pX, int pY);
    int getXInitialPosition(int pPiece, int pRotation);
    int getYInitialPosition(int pPiece, int pRotation);
    
};

/*Returns the type of a block (0 = no-block, 1 = normal block, 2 = pivot block)*/
int Pieces::getBlockType(int pPiece, int pRotation, int pX, int pY)
{
    return tetrisBlocks[pPiece][pRotation][pX][pY];
}

/*Returns the horizontal displacement of the piece that has to be applied in order to create it in the
correct position.*/
int Pieces::getXInitialPosition(int pPiece, int pRotation)
{
    return tetrisBlocksInitialPosition[pPiece][pRotation][0];
}

/*Returns the vertical displacement of the piece that has to be applied in order to create it in the
correct position.*/
int Pieces::getYInitialPosition(int pPiece, int pRotation)
{
    return tetrisBlocksInitialPosition[pPiece][pRotation][1];
}
#endif
