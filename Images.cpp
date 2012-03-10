#include "SDL.h"
#include <cmath>
#include "Surface.h"

void Image::shrink( double x=1.0, double y=1.0 )
{
	image = shrinkSurface(image, x, y);
}

void Image::shrink( double x_r=1.0, double y_r=1.0, int x=0, int y=0 )
{
	image = shrinkSurface(image, x_r, y_r);

	// Update the x and y pos's on screen
	on_screen_rect.x = x;
	on_screen_rect.y = y;
}
