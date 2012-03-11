#include "SDL.h"
#include <cmath>
#include "Surface.h"

void Image::shrink( double x=1.0, double y=1.0 )
{
	image = shrinkSurface(image, x, y);
}

void Image::rotate( double degree=0.0, double zoom=1.0, int smooth=1 )
{
	image = rotozoomSurface(image, degree, zoom, smooth);
	actual_rect = image->clip_rect;
}