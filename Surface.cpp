#include <cmath>
#include "SDL.h"
#include "Surface.h"

inline int abs(int x) { return x>=0 ? x : -x ;}
//inline int min( int a, int b )	{ return ( a<b ? a : b ); }

//----------------------------------------------------------------------------
// put_pixel functions for different bpp
//----------------------------------------------------------------------------
void put_pixel_bpp1( SDL_Surface * surface, int x, int y, Uint32 pixel )
{
	int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*p = pixel;
}

void put_pixel_bpp2( SDL_Surface* surface, int x, int y, Uint32 pixel )
{
	int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint16 *)p = pixel;
}

void put_pixel_bpp3( SDL_Surface * surface, int x, int y, Uint32 pixel )
{
	int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    if(SDL_BYTEORDER == SDL_BIG_ENDIAN) 
	{
		p[0] = (pixel >> 16) & 0xff;
		p[1] = (pixel >> 8) & 0xff;
        p[2] = pixel & 0xff;
	} 
	else
	{
		p[0] = pixel & 0xff;
        p[1] = (pixel >> 8) & 0xff;
        p[2] = (pixel >> 16) & 0xff;
    }
}

void put_pixel_bpp4( SDL_Surface * surface, int x, int y, Uint32 pixel )
{
	int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    *(Uint32 *)p = pixel;
}

Surface::Surface( int w, int h, int bpp, int flags )
	: fullscreen_(0), _w(w), _h(h)
{ 
	SDL_Init ( SDL_INIT_VIDEO | SDL_INIT_NOPARACHUTE );
	SDL_WM_SetCaption("Not Named", NULL);
	surface = SDL_SetVideoMode ( w, h, bpp, flags );
	
	if ( surface == NULL ) 
	{
        printf( "Unable to set 640x480 video: %s\n", SDL_GetError() );
		fflush(stdout);
        //exit(1);
    }
	atexit( SDL_Quit );

	bpp = surface->format->BytesPerPixel;

	switch (bpp)
	{
		case 1: put_pixel_fptr = &put_pixel_bpp1; break;
		case 2: put_pixel_fptr = &put_pixel_bpp2; break;
		case 3: put_pixel_fptr = &put_pixel_bpp3; break;
		case 4: put_pixel_fptr = &put_pixel_bpp4; break;
	}
}


void Surface::free()
{
	SDL_FreeSurface( surface );
}

Uint8 * Surface::get_pixel_addr( int x, int y )
{
	return (Uint8*)(Uint8*)surface->pixels + y * surface->pitch + x * bpp;
}

// Must call lock first
Uint32 Surface::get_pixel(int x, int y)
{
    int bpp = get_bpp();
    Uint8 * p = get_pixel_addr(x,y);

    switch (bpp) 
	{
		case 1: return *p;
		case 2: return *(Uint16 *)p;
		case 3: if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			        return p[0] << 16 | p[1] << 8 | p[2];
				else
					return p[0] | p[1] << 8 | p[2] << 16;
		case 4: return *(Uint32 *)p;
	    default:return 0;
    }
}


/////////////////////////////////////////////////////////////////////////
//Drawing Functions

//Images
void Surface::put_image(Image & i)
{
	SDL_BlitSurface(i.image, &(i.actual_rect), surface, &(i.on_screen_rect));
}

void Surface::put_image(Animated & a)
{
	SDL_BlitSurface(a.image, &(a.individual_rect), surface, &(a.on_screen_rect));
}

//Fill
void Surface::fill(const Color &c)
{
	SDL_Rect r; r.x = 0; r.y = 0; r.w = _w; r.h = _h;
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, c.r, c.g, c.b)); 
}

/////////////////////////////////////////////////////////////////////////


//----------------------------------------------------------------------------
// flip()
// Flips the buffers
//----------------------------------------------------------------------------
void Surface::flip()
{
	SDL_Flip( surface );
}


int Surface::get_bpp()
{
	return surface->format->BytesPerPixel;
}


void Surface::update_rect( int x, int y, int w, int h)
{
	SDL_UpdateRect ( surface, x, y, w, h );
}

//not sure if this is needed...
//Uint32 Surface::map_rgb( const SDL_Color & color )
//{
//	return SDL_MapRGB( surface->format, color.r, color.g, color.b );
//}


//----------------------------------------------------------------------------
// lock()
// Locks the surface
//----------------------------------------------------------------------------
void Surface::lock()
{
	if ( SDL_MUSTLOCK( surface ) ) SDL_LockSurface( surface );
}


//----------------------------------------------------------------------------
// unlock()
// Unlocks the surface
//----------------------------------------------------------------------------
void Surface::unlock()
{
	if ( SDL_MUSTLOCK( surface ) )
		SDL_UnlockSurface( surface );
}
