// io.h
// class that utilizes the SDL (Simple DirectMedia Layer) to create the
// game window, clear it, update its state, and handle player keyboard
// input.

// This is a personal project that was made by Dylan Connolly,
// based off of the C++ Tetris tutorial by Javier Lopez.
// Use is enabled under the Creative Commons public copyright license

// PREPROCESSOR DIRECTIVE
#ifndef _IO_
#define _IO_

// INCLUDES
//#ifndef __LINUX__
//#include "./SDL/include/SDL.h"
//#include "./SDL/SDL_GfxPrimitives/SDL_gfxPrimitives.h"
//#else
#include <SDL/SDL.h>
#include "SDL/SDL_GfxPrimitives/sdl_gfxprimitives.h"
//#endif
//#pragma comment (lib, "SDL/lib/SDL.lib")
//#pragma comment (lib, "SDL/SDL_GfxPrimitives/SDL_GfxPrimitives_Static.lib")

// ENUMS
enum color { BLACK, RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, WHITE, COLOR_MAX };

// ------ IO ------

class IO
{
public:

  // constructor, inits IO obj
  IO();

  // draws a rectangle of color pC at the positions passed in
  void drawRectangle( int pX1, int pY1, int pX2, int pY2, enum color pC );

  // clears the screen state
  void clearScreen();

  // getter, returns screen height
  int getScreenHeight();

  // SDL graphical initialization
  int initGraph();

  // polls all key event devices for key presses as game runs
  int pollKey();

  // ...
  int getKey();

  // returns the state of key pKey
  int isKeyDown( int pKey );

  // updates game state within SDL window
  void updateScreen();

};

#endif // _IO_
