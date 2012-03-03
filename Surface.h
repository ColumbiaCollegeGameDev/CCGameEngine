#ifndef SURFACE_H
#define SURFACE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "TextSurface.h"
#include "Color.h"
#include "Image.h"

#include "SDL_gfxPrimitives.h"

//----------------------------------------------------------------------------
// Constants
//----------------------------------------------------------------------------
const int WIDTH = 640;
const int HEIGHT = 480;
const int BPP = 0;
const int FLAGS = SDL_ANYFORMAT;

class SingletonSurface; // Use for making it a friend
class Image;

inline int min( int a, int b )	{ return ( a<b ? a : b ); }


class Surface{

public:
	Surface( int=WIDTH, int=HEIGHT, int=BPP, int=SDL_ANYFORMAT );	
	~Surface() { SDL_FreeSurface( surface ); }
	
	bool fullscreen_;
	void free();
	void fullscreen(int n = -1, int ww = -1, int hh = -1)
	{
		if (ww == -1){ ww = _w; hh = _h;}
		else {_w = ww; _h = hh;}
		if (n == -1) n = (fullscreen_ == 0 ? 1 : 0);
		if (n && !fullscreen_)
		{
			surface = SDL_SetVideoMode ( _w, _h, BPP, SDL_FULLSCREEN);
			fullscreen_ = 1;
			return;
		}
		if (!n && fullscreen_)
		{
			surface = SDL_SetVideoMode ( _w, _h, BPP, SDL_ANYFORMAT);
			fullscreen_ = 0;
			return;
		}
	}
	int  get_bpp();
    	void lock();
	void unlock();
	void update_rect( int=0, int=0, int=0, int=0 );
	void flip();

	inline Uint32 map_rgb( const Color & color );

	Uint32	get_pixel( int, int );
	Uint8*	get_pixel_addr( int, int );
	
	
	//------------------------------------------------------------------------
	// Returns pointer to SDL_Surface (only for testing)
	//------------------------------------------------------------------------
	SDL_Surface * get() { return surface; }

private:
	int _w, _h;
	friend class SingletonSurface;
//	Surface( int=WIDTH, int=HEIGHT, int=BPP, int=SDL_ANYFORMAT );
	SDL_Surface * surface;
	Uint32 bpp;
	void   (*put_pixel_fptr) ( SDL_Surface*, int, int, Uint32 );
};

#endif
