#include <iostream>
#include "SDL.h"
#include "Surface.h"
#include "Input.h"

const int WINDOW_W = 640;
const int WINDOW_H = 480;

int main(int argc, char* argv[])
{
	Surface surface(WINDOW_W, WINDOW_H);
	SDL_Event event;
	Mouse_Input mouse;
	Keyboard keyboard;
	
	while (1)
	{
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		//Handle the events
		bool end_game = 0;
		mouse.reset();
		keyboard.reset();
		while (SDL_PollEvent(&event))
			switch(event.type)
			{
			case SDL_QUIT: end_game = 1; break;
			case SDL_MOUSEBUTTONDOWN:
			        mouse.pressed(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.released(event.button.button);
				break;
			case SDL_KEYDOWN: 
				keyboard.pressed(event.key.keysym.sym);
				break;
			case SDL_KEYUP: 
				keyboard.released(event.key.keysym.sym);
				break;
			}
		if (end_game) break;		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		
		surface.flip();
		SDL_Delay(10);
	}
	return 0;
}
