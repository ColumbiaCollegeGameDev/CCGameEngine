#ifndef SURFACE_H
#define SURFACE_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "Images.h"
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

class Color
{
public:
	Color(int r_, int g_, int b_, int a_ = 255)
		: r(r_), g(g_), b(b_), a(a_)
	{
	}
	
	unsigned char r, g, b, a;
};
const Color BLACK = Color(0, 0, 0);
const Color WHITE = Color(255, 255, 255);

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

	//not sure if this is needed...
	//inline Uint32 map_rgb( const Color & color );

	Uint32	get_pixel( int, int );
	Uint8*	get_pixel_addr( int, int );
	
	/////////////////////////////////////////////////////////////////////////
	//Drawing Functions
	
	//Images
	void put_image(Image &);
	void put_image(Animated &);
	void put_image(Image &i, int x, int y)
	{
		i.on_screen_rect.x = x;
		i.on_screen_rect.y = y;
		put_image(i);
	}
	void put_image(Animated &a, int x, int y)
	{
		a.on_screen_rect.x = x;
		a.on_screen_rect.y = y;
		put_image(a);
	}
	
	//////////////////////
	//Drawing functions usually require 4 parts of the color: red, green, blue, and alpha...
	//////////////////////
	
	//Pixel
	void put_pixel(short, short, unsigned char, unsigned char, unsigned char, unsigned char);
	void put_pixel(short x, short y, const Color &c)
	{
		put_pixel(x, y, c.r, c.g, c.b, c.a);
	}
	
	//Line
	void put_line(short, short, short, short, unsigned char, unsigned char, unsigned char, unsigned char);
	void put_line(short x1, short y1, short x2, short y2, const Color &c)
	{
		put_line(x1, y1, x2, y2, c.r, c.g, c.b, c.a);
	}
	void put_line_aa(short, short, short, short, unsigned char, unsigned char, unsigned char, unsigned char);
	void put_line_aa(short x1, short y1, short x2, short y2, const Color &c)
	{
		put_line_aa(x1, y1, x2, y2, c.r, c.g, c.b, c.a);
	}
	
	//Rectangle
	void put_rect(short, short, short, short, unsigned char, unsigned char, unsigned char, unsigned char, bool fill = 1);
	void put_rect(short x1, short y1, short x2, short y2, const Color &c, bool fill = 1)
	{
		put_rect(x1, y1, x2, y2, c.r, c.g, c.b, c.a, fill);
	}
	
	//Circle
	void put_circle(short, short, short, unsigned char, unsigned char, unsigned char, unsigned char, bool fill = 1);
	void put_circle(short x1, short y1, short r, const Color &c, bool fill = 1)
	{
		put_circle(x1, y1, r, c.r, c.g, c.b, c.a, fill);
	}
	void put_circle_aa(short, short, short, unsigned char, unsigned char, unsigned char, unsigned char); // no fill function for aa circle
	void put_circle_aa(short x1, short y1, short r, const Color &c)
	{
		put_circle_aa(x1, y1, r, c.r, c.g, c.b, c.a);
	}
	
	//Ellipse
	void put_ellipse(short, short, short, short, unsigned char, unsigned char, unsigned char, unsigned char, bool fill = 1);
	void put_ellipse(short x1, short y1, short rx, short ry, const Color &c, bool fill = 1)
	{
		put_ellipse(x1, y1, rx, ry, c.r, c.g, c.b, c.a, fill);
	}
	void put_ellipse_aa(short, short, short, short, unsigned char, unsigned char, unsigned char, unsigned char); // no fill function for aa ellipse
	void put_ellipse_aa(short x1, short y1, short rx, short ry, const Color &c)
	{
		put_ellipse_aa(x1, y1, rx, ry, c.r, c.g, c.b, c.a);
	}
	
	//Polygon
	void put_polygon(short *x, short *y, short, unsigned char, unsigned char, unsigned char, unsigned char, bool fill = 1);
	void put_polygon(short *x, short *y, short n, const Color &c, bool fill = 1)
	{
		put_polygon(x, y, n, c.r, c.g, c.b, c.a, fill);
	}
	void put_polygon_aa(short *x, short *y, short, unsigned char, unsigned char, unsigned char, unsigned char); // no fill function for aa ellipse
	void put_polygon_aa(short *x, short *y, short n, const Color &c)
	{
		put_polygon_aa(x, y, n, c.r, c.g, c.b, c.a);
	}
	
	//Fill
	void fill(const Color &c);
	
	//Strings
	void put_text(short x, short y, const char *, unsigned char, unsigned char, unsigned char, unsigned char);
	void put_text(short x, short y, const char *ch, const Color &c)
	{
		put_text(x, y, ch, c.r, c.g, c.b, c.a);
	}
	
	/////////////////////////////////////////////////////////////////////////
	
	
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
