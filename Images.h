#ifndef IMAGES_H
#define IMAGES_H

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_rotozoom.h>
#include "Surface.h"

class Image{

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
	// Blits the shrinked image by x and y ratios
	void shrink( Surface surf, double x=1.0, double y=1.0 )
	{
		Image shrunk(*this);

		shrunk.image = shrinkSurface(shrunk.image, x, y);
		surf.put_image(shrunk);
	}
	
	SDL_Surface *image;
	SDL_Rect actual_rect, on_screen_rect;

};

class Animated
{
public:
	Animated(const char * filename, short delay_ = 0, bool reverse_ = 0)
		: image(IMG_Load(filename)), frame(0), advance_dir(1), delay(delay_), reverse(0), delay_count(0)
	{
		if (image == NULL)
		{
			printf("Error in Image::Image(): No image file %s\n", filename);
			exit(1);
		}
		actual_rect = image->clip_rect;
		individual_rect = actual_rect;
		determine_size();
	}
	Animated(const char * filename, short w, short h, short delay_ = 0, bool reverse_ = 0)
		: image(IMG_Load(filename)), frame(0), advance_dir(1), delay(delay_), reverse(reverse_), delay_count(0)
	{
		if (image == NULL)
		{
			printf("Error in Image::Image(): No image file %s\n", filename);
			exit(1);
		}
		actual_rect = image->clip_rect;
		individual_rect = actual_rect;
		individual_rect.w = w;
		individual_rect.h = h;
		if (actual_rect.w < actual_rect.h)
		{
			is_horizontal = 0;
			frames = actual_rect.h / individual_rect.h;
		}
		else
		{
			is_horizontal = 1;
			frames = actual_rect.w / individual_rect.w;
		}
	}
	~Animated()
	{
	 	SDL_FreeSurface(image);
	}
	
	void determine_size()//this makes the individual rect a square based on w or h
	{
		individual_rect = actual_rect;
		
		if (actual_rect.w < actual_rect.h) // image is vertical based
		{
			individual_rect.w = actual_rect.w;
			individual_rect.h = actual_rect.w;
			is_horizontal = 0;
			frames = actual_rect.h / individual_rect.h;
		}
		else // image is horizontal based
		{
			individual_rect.w = actual_rect.h;
			individual_rect.h = actual_rect.h;
			is_horizontal = 1;
			frames = actual_rect.w / individual_rect.w;
		}
		on_screen_rect = individual_rect;
	}
	
	void step() // must call to have the image actually animate.
	{
		//delay causes a delay to slow down the animation
		//reverse determines whether or not the frame step follows a sine wave ex: 1234321234321 vs 123412341234
		if (delay_count < delay) {delay_count++; return;}
		else
			delay_count = 0;
			
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
	short frame, frames, delay, delay_count;
	bool reverse, advance_dir, is_horizontal;
};

#endif

