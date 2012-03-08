#include "SDL.h"
#include <cmath>
#include "Surface.h"

void Image::shrink( Surface s, double x=1.0, double y=1.0 )
{
	Image shrunk(*this);

	shrunk.image = shrinkSurface(shrunk.image, x, y);
	s.put_image(shrunk);
}

void Image::shrink( Surface s, double x_r=1.0, double y_r=1.0, int x=0, int y=0 )
{
	Image shrunk(*this);

	shrunk.image = shrinkSurface(shrunk.image, x_r, y_r);

	// Update the x and y pos's on screen
	on_screen_rect.x = x;
	on_screen_rect.y = y;

	s.put_image(shrunk);
}
