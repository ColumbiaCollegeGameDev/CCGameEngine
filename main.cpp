#include <iostream>
#include "SDL.h"
#include "Surface.h"

const int WINDOW_W = 640;
const int WINDOW_H = 480;

int main()
{
	Surface surface(WINDOW_W, WINDOW_H);
	
	
	surface.flip();
	SDL_Delay(2000);
	return 0;
}
