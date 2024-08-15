// game.cpp
// class that represents related aspects pertaining to the game,
// such as initializing the game, drawing the board/pieces using
// IO class (utilizes SDL), and creating new random pieces.

// This is a personal project that was made by Dylan Connolly,
// based off of the C++ Tetris tutorial by Javier Lopez.
// Use is enabled under the Creative Commons public copyright license

// INCLUDES
#include "game.h"

// init
Game::Game( Board* pBoard, Pieces* pPieces, IO* pIO, int pScreenHeight )
{
  // get screen height  
  mScreenHeight = pScreenHeight;

  // get the pointer to the board and pieces classes
  mBoard = pBoard;
  mPieces = pPieces;
  mIO = pIO;

  // game initialization
  initGame();
}

// get a random int within the range of pA to pB
int Game::getRand( int pA, int pB )
{
  return rand() % ( pB - pA + 1 ) + pA;
}

// initial parameters of the game after starting
void Game::initGame()
{
  // init random numbers
  srand( ( unsigned int ) time( NULL ) );

  // first piece
  mPiece = getRand( 0, 6 );
  mRotation = getRand( 0, 3 );
  mPosX = ( BOARD_WIDTH / 2 ) + mPieces->getXInitialPos( mPiece, mRotation );
  mPosY = mPieces->getYInitialPos( mPiece, mRotation );

  // next piece
  mNextPiece = getRand( 0, 6 );
  mNextRotation = getRand( 0, 3 );
  mNextPosX = BOARD_WIDTH + 5;
  mNextPosY = 5;
};

// create a random piece
void Game::createNewPiece()
{
  mPiece = mNextPiece;
  mRotation = mNextRotation;
  mPosX = ( BOARD_WIDTH / 2 ) + mPieces->getXInitialPos( mPiece, mRotation );
  mPosY = mPieces->getYInitialPos( mPiece, mRotation );

  // random next piece
  mNextPiece = getRand( 0, 6 );
  mNextRotation = getRand( 0, 3 );
}

// draw a piece on the game board (iterates through 5x5 piece matrix, drawing each block of the piece)
// ( in our implementation, the normal blocks will be green and the pivot blocks will be blue )
void Game::drawPiece( int pX, int pY, int pPiece, int pRotation )
{
  color mColor; // color of the block

  // obtain the position in pixels on the screen for the block we want to draw
  int mPixelsX = mBoard->getXPosInPixels( pX );
  int mPixelsY = mBoard->getYPosInPixels( pY );

  // traverse the matrix of blocks of the piece and draw them appropriately
  for ( int i = 0; i < PIECE_BLOCKS; i++ )
  {
    for ( int j = 0; j < PIECE_BLOCKS; j++ )
    {
      // get the type of the block and draw it with the correct color
      switch ( mPieces->getBlockType( pPiece, pRotation, j, i ) )
      {
        case 1:
          mColor = GREEN;
          break;
        case 2:
          mColor = BLUE;
          break;
      }

      if ( mPieces->getBlockType( pPiece, pRotation, j, i ) != 0 )
      {
        mIO->drawRectangle( ( mPixelsX + i * BLOCK_SIZE ),
                            ( mPixelsY + j * BLOCK_SIZE ),
                            ( mPixelsX + i * BLOCK_SIZE ) + BLOCK_SIZE - 1,
                            ( mPixelsY + j * BLOCK_SIZE ) + BLOCK_SIZE - 1,
                            ( mColor ) );
      } // end if
    } // end j for
  } // end i for
}
                        
// draw board, draws the two lines that delimit the game grid
void Game::drawBoard()
{
  // calculate the limits of the board in pixels
  int mX1 = BOARD_POSITION - ( BLOCK_SIZE * ( BOARD_WIDTH / 2 ) ) - 1;
  int mX2 = BOARD_POSITION + ( BLOCK_SIZE * ( BOARD_WIDTH / 2 ) );
  int mY = mScreenHeight - ( BLOCK_SIZE * BOARD_HEIGHT );

  // check that the vertical margin is not too small
  // assert( mY > MIN_VERTICAL_MARGIN );

  // rectangles that delimit the board
  mIO->drawRectangle( mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE );
  mIO->drawRectangle( mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE );

  // check that the horizontal margin is not too small
  // assert( mX1 > MIN_HORIZONTAL_MARGIN );

  // draw the blocks that are already on the board
  mX1 += 1;
  for ( int i = 0; i < BOARD_WIDTH; i++ )
  {
    for ( int j = 0; j < BOARD_HEIGHT; j++ )
    {
      // check if the block is filled. if so, draw it
      if ( !mBoard->isFreeBlock( i, j ) )
      {
        mIO->drawRectangle( ( mX1 + i * BLOCK_SIZE ),
                            ( mY + j * BLOCK_SIZE ),
                            ( mX1 + i * BLOCK_SIZE ) + BLOCK_SIZE - 1,
                            ( mY + j * BLOCK_SIZE ) + BLOCK_SIZE - 1,
                            ( RED ) );
      } // end if
    } // end j for
  } // end i for
}

// utilizes the drawBoard() and drawPiece methods to draw entire individual game scene
void Game::drawScene()
{
  // draw the game grid delimitation lines and any blocks already stored
  drawBoard();

  // draw the currently descending piece
  drawPiece( mPosX, mPosY, mPiece, mRotation );

  // draw the next piece to descend
  drawPiece( mNextPosX, mNextPosY, mNextPiece, mNextRotation );
}
