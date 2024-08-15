// board.h
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

#ifndef _BOARD_
#define _BOARD_

// INCLUDES

#include "pieces.h"

// DEFINES

#define BOARD_LINE_WIDTH 6            // width of each of the two lines that delimit the board
#define BLOCK_SIZE 16                 // width and height of each block from a piece
#define BOARD_POSITION 320            // center position of the board from the left of the screen
#define BOARD_WIDTH 10                // board width in blocks
#define BOARD_HEIGHT 20               // board height in blocks
#define MIN_VERTICAL_MARGIN 20        // minimum vertical margin for the board limit
#define MIN_HORIZONTAL_MARGIN 20      // minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5                // number of horizontal and vertical blocks of a matrix piece

// ------ Board ------

class Board
{
public:

  // constructor, takes pointer to a Pieces obj & int representing piece screen height
  Board( Pieces* pPieces, int pScreenHeight );

  // setters & getters
  int getXPosInPixels( int pPos );
  int getYPosInPixels( int pPos );
  bool isFreeBlock( int pX, int pY );
  bool isPossibleMovement( int pX, int pY, int pPiece, int pRotation );
  void storePiece( int pX, int pY, int pPiece, int pRotation );
  void deletePossibleLines();
  bool isGameOver();

private:

  // POS_FREE = free square on the board
  // POS_FILLED = filled square on the board
  enum { POS_FREE, POS_FILLED };

  // board that contains the pieces in play
  int mBoard[BOARD_WIDTH][BOARD_HEIGHT];

  Pieces* mPieces;
  int mScreenHeight;

  // private helper funcs
  void initBoard();
  void deleteLine( int pY );

};
 
#endif
