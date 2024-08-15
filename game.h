// game.h
// class that represents related aspects pertaining to the game,
// such as initializing the game, drawing the board/pieces using
// IO class (utilizes SDL), and creating new random pieces.

// This is a personal project that was made by Dylan Connolly,
// based off of the C++ Tetris tutorial by Javier Lopez.
// Use is enabled under the Creative Commons public copyright license

#ifndef _GAME_
#define _GAME_

// INCLUDES
#include "board.h"
#include "pieces.h"
#include "io.h"
#include <time.h>

// DEFINES
#define WAIT_TIME 700           // number of milliseconds that the piece remains before descending a block

// ------ game ------
class Game
{
public:

  // constructor, takes a Board ptr, Pieces ptr, IO ptr, and int pScreenHeight
  Game( Board* pBoard, Pieces* pPieces, IO* pIO, int pScreenHeight );

  // draws current game scene (refreshes display essentially)
  void drawScene();
  // creates a new random piece from the 4-dimensional array
  void createNewPiece();

  int mPosX, mPosY;             // position of the piece that is descending
  int mPiece, mRotation;        // kind and rotation of the piece that is descending

private:

int mScreenHeight;              // screen height in pixels
int mNextPosX, mNextPosY;       // position of the next piece
int mNextPiece, mNextRotation;  // kind and rotation of the next piece

Board* mBoard;
Pieces* mPieces;
IO* mIO;

// private helper functions
int getRand( int pA, int pB );
void initGame();
void drawPiece( int pX, int pY, int pPiece, int pRotation );
void drawBoard();

};

#endif // _GAME_
