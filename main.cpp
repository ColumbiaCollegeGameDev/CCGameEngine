#include <iostream>
#include "SDL.h"
#include "Surface.h"
#include "Input.h"

const int WINDOW_W = 640;
const int WINDOW_H = 480;

int main(int argc, char* argv[])
{
	Surface surface(WINDOW_W, WINDOW_H);
	Events input;
	const Mouse_Input *MOUSE = &(input.mouse);    //holds the input's mouse object for easier reference.
	const Keyboard *KEYBOARD = &(input.keyboard); //holds the input's keyboard object for easier reference.
	
	while (1)
	{
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		//Handle the events
		bool end_game = 0;
		int input_result = input.update();
		switch(input_result)
		{
		case -1: end_game = 1;
		}
		if (end_game) break;		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		
		//std::cout << MOUSE->mouse_x << "; " << KEYBOARD->key_down(SDLK_SPACE) << std::endl;
		
		surface.flip();
		SDL_Delay(10);
	}
	return 0;
}
