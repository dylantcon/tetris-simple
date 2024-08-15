#ifndef _PIECES_
#define _PIECES_

// Pieces class, made by Dylan Connolly
// Based off of the C++ Tetris tutorial by Javier Lopez
// Use is enabled under the Creative Commons public copyright license

class Pieces
{
public:

  int getBlockType( int pPiece, int pRotation, int pX, int pY );
  int getXInitialPos( int pPiece, int pRotation );
  int getYInitialPos( int pPiece, int pRotation );

};

#endif // _PIECES_
