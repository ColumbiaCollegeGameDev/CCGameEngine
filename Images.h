#ifndef IMAGES_H
#define IMAGES_H

#include "SDL.h"
#include "SDL_image.h"

class Image
{
public:
	Image(const char * filename)
		: image(IMG_Load(filename))
	{
		if (image == NULL)
		{
			printf("Error in Image::Image(): No image file %s\n", filename);
			exit(1);
		}
		actual_rect = image->clip_rect;
		on_screen_rect = actual_rect;
	}
	~Image()
	{
	 	SDL_FreeSurface(image);
	}
	
	SDL_Surface *image;
	SDL_Rect actual_rect, on_screen_rect;
};

class Animated
{
public:
	Animated(const char * filename)
		: image(IMG_Load(filename)), frame(0), advance_dir(1)
	{
		if (image == NULL)
		{
			printf("Error in Image::Image(): No image file %s\n", filename);
			exit(1);
		}
		actual_rect = image->clip_rect;
		individual_rect = actual_rect;
		
		if (actual_rect.w < actual_rect.h) // image is vertical based
		{
			individual_rect.w = actual_rect.w;
			individual_rect.h = actual_rect.w;
			is_horizontal = 0;
			frames = actual_rect.h / actual_rect.w;
		}
		else // image is horizontal based
		{
			individual_rect.w = actual_rect.h;
			individual_rect.h = actual_rect.h;
			is_horizontal = 1;
			frames = actual_rect.w / actual_rect.h;
		}
		on_screen_rect = individual_rect;
	}
	~Animated()
	{
	 	SDL_FreeSurface(image);
	}
	
	void step() // must call to have the image actually animate.
	{
		frame += 1 * (advance_dir ? 1 : -1);
		if (frame >= frames)
		{
			if (reverse)
			{
				frame = frames - 2;
				advance_dir = 0;
			}
			else
				frame = 0;
		}
		if (frame < 0)
		{
			if (reverse)
			{
				frame = 1;
				advance_dir = 1;
			}
			else
				frame = frames - 1;
		}
		if (is_horizontal)
			individual_rect.x = frame * individual_rect.w;
		else
			individual_rect.y = frame * individual_rect.h;
	}
	
	SDL_Surface *image;
	SDL_Rect actual_rect, individual_rect, on_screen_rect;
private:
	short frame, frames;
	bool reverse, advance_dir, is_horizontal;
};

#endif
