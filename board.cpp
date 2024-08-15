// board.cpp
// Represents a board of the Tetris game. Is a matrix of N x N squares.

// This is a personal project that was made by Dylan Connolly,
// based off of the C++ Tetris tutorial by Javier Lopez.
// Use is enabled under the Creative Commons public copyright license

/* 
 * Stores pieces in the board and checks for collisions. Stores a
 * bidimensional array of N x N squares that are initialized to
 * POS_FREE. The pieces will be stored by filling these blocks when
 * they fall down, updating the block to POS_FILLED. 
 */ 

// INCLUDES
#include "board.h"

// board constructor initialization method
Board::Board( Pieces* pPieces, int pScreenHeight )
{
  // get screen height
  mScreenHeight = pScreenHeight;

  // get the pointer to the pieces class
  mPieces = pPieces;

  // init the board blocks with free positions
  initBoard();
}

// init the board with POS_FREE positions for every square in N x N
void Board::initBoard()
{
  for ( int i = 0; i < BOARD_WIDTH; i++ )
    for ( int j = 0; j < BOARD_HEIGHT; j++ )
      mBoard[i][j] = POS_FREE;
}

// store a piece in the board by filling the blocks 
// ( pX, pY, pPiece, pRotation follow same semantic meaning as in pieces.cpp )
void Board::storePiece( int pX, int pY, int pPiece, int pRotation )
{
  // store each square of the piece into the board
  for ( int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++ )
  {
    for ( int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++ )
    {
      // store only the squares of the piece that are not empty [0]
      if ( mPieces->getBlockType( pPiece, pRotation, j2, i2 ) != 0 )
        mBoard[i1][j1] = POS_FILLED;
    }
  }
}

// check to see if the game has ended (piece attained top position)
bool Board::isGameOver()
{
  // if the first line has blocks, then you lose
  for ( int i = 0; i < BOARD_WIDTH; i++ )
    if ( mBoard[i][0] == POS_FILLED )
      return true;
  return false;
}

// delete a line of the board by moving all of the lines down
void Board::deleteLine( int pY )
{
  // moves all the upper lines one row down
  for ( int j = pY; j > 0; j-- )
    for ( int i = 0; i < BOARD_WIDTH; i++ )
      mBoard[i][j] = mBoard[i][j - 1];
}

// delete all the lines that should be removed
void Board::deletePossibleLines()
{
  for ( int j = 0; j < BOARD_HEIGHT; j++ )
  {
    int i = 0;
    while ( i < BOARD_WIDTH )
    {      
      if ( mBoard[i][j] != POS_FILLED )
        break;
      i++;
    }

    if ( i == BOARD_WIDTH )
      deleteLine( j );
  }
}    

// returns true if this block of the board is empty, and false if filled
bool Board::isFreeBlock( int pX, int pY )
{
  if ( mBoard[pX][pY] == POS_FREE )
    return true;
  return false;
}

// returns the horizontal position (in pixels) of the block, given pPos
int Board::getXPosInPixels( int pPos )
{
  return ( ( BOARD_POSITION - ( BLOCK_SIZE * ( BOARD_WIDTH / 2 ) ) ) + ( pPos * BLOCK_SIZE ) );
}

int Board::getYPosInPixels( int pPos )
{
  return ( ( mScreenHeight - ( BLOCK_SIZE * BOARD_HEIGHT ) ) + ( pPos * BLOCK_SIZE ) );
}

/*
 * check if the piece can be stored at given position without any collision,
 * returns true if movement is possible, false if not
 */
bool Board::isPossibleMovement( int pX, int pY, int pPiece, int pRotation )
{
  // checks collision with pieces already stored in the board OR the board limits
  // this is just to check the 5x5 blocks of a piece with the appropriate area in the board
  for ( int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++ )
  {
    for ( int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++ )
    {
      // check if the piece is outside the limits of the board
      if ( i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1 )
      {
        if ( mPieces->getBlockType( pPiece, pRotation, j2, i2 ) != 0 )
          return false;
      }
      // check if the piece has collided with a block already in the board
      if ( j1 >= 0 )
      {
        if ( ( mPieces->getBlockType( pPiece, pRotation, j2, i2 ) != 0 ) && ( !isFreeBlock( i1, j1 ) ) )
          return false;
      }
    }
  }
  // if prog. reaches this point, no collision has occurred
  return true;
}
