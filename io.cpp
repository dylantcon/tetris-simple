// io.cpp
// This file contains the definitions of all methods outlined in
// io.h, pertaining to operations within the SDL window as the
// Tetris game is running. 

// This is a personal project that was made by Dylan Connolly,
// based off of the C++ Tetris tutorial by Javier Lopez.
// Use is enabled under the Creative Commons public copyright license

// To clarify, as I am still an undergraduate comp-sci student, most
// of this crap makes zero sense to me. As such, the source code from
// Javier Lopez' example implementation was used.

// INCLUDES
#include "io.h"

static SDL_Surface* mScreen;                         // screen
static Uint32 mColors [COLOR_MAX] =  { 0x000000ff,   // colors
                                       0xff0000ff,
                                       0x00ff00ff,
                                       0x0000ffff,
                                       0x00ffffff,
                                       0xff00ffff,
                                       0xffff00ff,
                                       0xffffffff };
                                      
// init
IO::IO()
{
  initGraph();
}

// clear the screen to black
void IO::clearScreen()
{
  boxColor( mScreen, 0, 0, mScreen->w-1, mScreen->h-1, mColors[BLACK] );
}

// draw a rectangle of given color
// pX1, pY1 : upper left corner of rectangle
// pX2, pY2 : lower right corner of rectangle
// pC : rectangle color
void IO::drawRectangle( int pX1, int pY1, int pX2, int pY2, enum color pC )
{
  boxColor( mScreen, pX1, pY1, pX2, pY2-1, mColors[pC] );
}

// return the screen height
int IO::getScreenHeight()
{
  return mScreen->h;
}

// update screen state using SDL_Flip( ... )
void IO::updateScreen()
{
  SDL_Flip( mScreen );
}

// keyboard input
int IO::pollKey()
{
  SDL_Event event;
  while ( SDL_PollEvent( &event ) )
  {
    switch ( event.type )
    {
      case SDL_KEYDOWN:
        return event.key.keysym.sym;
      case SDL_QUIT:
        exit(3);
    }
  }
  return -1;
}

// keyboard input
int IO::getKey()
{
  SDL_Event event;
  while ( true )
  {
    SDL_WaitEvent( &event );
    if ( event.type == SDL_KEYDOWN )
      break;
    if ( event.type == SDL_QUIT )
      exit(3);
  };
  return event.key.keysym.sym;
}

// keyboard input
int IO::isKeyDown( int pKey )
{
  Uint8* mKeytable;
  int mNumkeys;
  SDL_PumpEvents();
  mKeytable = SDL_GetKeyState( &mNumkeys );
  return mKeytable[pKey];
}

// SDL Graphical Initialization
int IO::initGraph()
{
  const SDL_VideoInfo* info;
  Uint8  video_bpp;
  Uint32 videoflags;

  // initialize SDL
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    fprintf( stderr, "Couldn't initialize SDL: %s\n", SDL_GetError() );
    return 1;
  }  
  atexit( SDL_Quit );

  // alpha blending doesn't work well at 8-bit color
  info = SDL_GetVideoInfo();
  if ( info->vfmt->BitsPerPixel > 8 )
    video_bpp = info->vfmt->BitsPerPixel;
  else
    video_bpp = 16;

  videoflags = SDL_SWSURFACE | SDL_DOUBLEBUF;

  // set 640x480 video mode
  if ( ( mScreen = SDL_SetVideoMode( 640, 480, video_bpp, videoflags ) ) == NULL )
  {
    fprintf( stderr, "Couldn't set %ix%i video mode: %s\n", 640, 480, SDL_GetError() );
    return 2;
  }
  return 0;
}
    
























