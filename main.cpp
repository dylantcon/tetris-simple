// main.cpp
// This is the driver program for the lightweight Tetris game. 
// For each frame, we draw the state of the board to reflect
// the current piece positions. After this is done, we utilize
// keyboard input to move the piece. Before each movement is
// conducted, checks are made to see if they are possible. We
// also will measure the time in order to facilitate the piece
// descending every n milliseconds. Whenever a descent occurs,
// we must check to see if the movement is valid. If it is not,
// then we know that the piece has landed and must then be 
// stored on the game grid. We also will perform checks to see
// if there are blocks in the upper row, if so, the game is over.


// ****** TETRIS GAME CONTROLS ******
// A: Move piece left by 1
// S: Descend piece by 1
// D: Move piece right by 1
// X: Descend piece until collision
// Q: Rotate piece CCW (positive rad)
// E: Rotate piece CW (negative rad)
// **********************************


// This is a personal project that was made by Dylan Connolly,
// based off of the C++ Tetris tutorial by Javier Lopez.
// Use is enabled under the Creative Commons public copyright license

#include "game.h"
#ifndef __LINUX__
#include <windows.h>
#endif

// ------ main -------

//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow ) // for windows users
int main()
{
  // VARS
  // IO class is for drawing stuff, uses SDL for the rendering. See io.h for more information,
  // if it is desired to use a different renderer you must change the methods of this class
  
  // IO
  IO mIO;
  int mScreenHeight = mIO.getScreenHeight();

  // pieces
  Pieces mPieces;

  // board
  Board mBoard( &mPieces, mScreenHeight );

  // game
  Game mGame( &mBoard, &mPieces, &mIO, mScreenHeight );

  // get the actual clock ms (SDL)
  unsigned long mTime1 = SDL_GetTicks();

  // the block below contains the main game loop, which may be exited by pressing ESC
  while ( !mIO.isKeyDown( SDLK_ESCAPE ) )
  {
    // drawing steps
    mIO.clearScreen();
    mGame.drawScene();
    mIO.updateScreen();

    // keyboard input parsing
    int mKey = mIO.pollKey();

    switch ( mKey )
    {
      case ( SDLK_d ): // key D, attempt to move block right
      {
        if ( mBoard.isPossibleMovement( mGame.mPosX+1, mGame.mPosY, mGame.mPiece, mGame.mRotation ) )
        {
          mGame.mPosX++;
          break;
        }
      }
      case ( SDLK_a ): // key A, attempt to move block left
      {
        if ( mBoard.isPossibleMovement( mGame.mPosX-1, mGame.mPosY, mGame.mPiece, mGame.mRotation ) )
        {
          mGame.mPosX--;
          break;
        }
      }
      case ( SDLK_s ): // key S, attempt to descend piece by 1 block
      {
        if ( mBoard.isPossibleMovement( mGame.mPosX, mGame.mPosY+1, mGame.mPiece, mGame.mRotation ) )
        {
          mGame.mPosY++;
          break;
        }
      }
      case ( SDLK_x ): // key X, descends piece while no collision is detected
      {
        // while our current position is valid, descend piece
        while ( mBoard.isPossibleMovement( mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation ) )
          mGame.mPosY++;

        // while loop has exited with our mPosY invalidating the position by 1; thus valid pos @ mPosY - 1
        mBoard.storePiece( mGame.mPosX, mGame.mPosY-1, mGame.mPiece, mGame.mRotation );
        // if any full rows of 10 squares resulted from storage in board, delete them
        mBoard.deletePossibleLines();

        // check to see if any squares are now in upper row (ends game)
        if ( mBoard.isGameOver() )
        {
          mIO.getKey();
          exit(0);
        }
        
        // now, make a new piece to replace the one that was fully descended
        mGame.createNewPiece();
        break;
      }
      case ( SDLK_e ): // key E, rotates CW (negative rad)      
      {
        // ( num + 1 ) % 4 allows wrap-around to 0 if num > 3.
        if ( mBoard.isPossibleMovement( mGame.mPosX, mGame.mPosY, mGame.mPiece, ( mGame.mRotation + 1 ) % 4 ) )
          mGame.mRotation = ( mGame.mRotation + 1 ) % 4;
        break;
      }
      case ( SDLK_q ): // key Q, rotates CCW (positive rad)
      {
        // ( ( num - 1 ) % 4 + 4 ) % 4 allows wrap-around to 3 if num < 0.
        if ( mBoard.isPossibleMovement( mGame.mPosX, mGame.mPosY, mGame.mPiece,( ( ( mGame.mRotation - 1 ) % 4 + 4 ) % 4 ) ) )
          mGame.mRotation = ( ( mGame.mRotation - 1 ) % 4 + 4 ) % 4;
        break;
      }
    } // end of keyboard input parsing switch


    // vertical movement ( non-player incurred descent )
    // get new 'newer' time
    unsigned long mTime2 = SDL_GetTicks();

    // if the difference between the older and newer times is greater than the descent wait time...
    if ( ( mTime2 - mTime1 ) > WAIT_TIME )
    {
      // check to see if the non-player incurred descent is possible, if so, descend piece
      if ( mBoard.isPossibleMovement( mGame.mPosX, mGame.mPosY+1, mGame.mPiece, mGame.mRotation ) )
      {
        mGame.mPosY++;
      }
      // if non-player incurred descent is not possible, then we have collided. store block on game grid
      else
      {        
        mBoard.storePiece( mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation );
        // if any full rows of 10 squares resulted from storage in board, delete them
        mBoard.deletePossibleLines();

        // check to see if any squares are now in upper row (ends game) 
        if ( mBoard.isGameOver() )
        {
          mIO.getKey();
          exit(0);
        }
        // now, make a new piece to replace the one that descended til collision
        mGame.createNewPiece();
      }
      // get new 'older' time
      mTime1 = SDL_GetTicks();          
    }
  } // end while loop
  
  return 0;
} // end main
