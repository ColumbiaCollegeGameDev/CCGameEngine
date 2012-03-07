#include <iostream>
#include "SDL.h"
#include "Surface.h"
#include "Input.h"
#include "Images.h"

const int WINDOW_W = 640;
const int WINDOW_H = 480;

int main(int argc, char* argv[])
{
	Surface surface(WINDOW_W, WINDOW_H);
	Events input;
	const Mouse_Input *MOUSE = &(input.mouse);    //holds the input's mouse object for easier reference.
	const Keyboard *KEYBOARD = &(input.keyboard); //holds the input's keyboard object for easier reference.
	Animated player_run("images/player/player_jungle_run.png", 72, 122, 10);  //filename, width of frame, height of frame, delay
	Animated player_jump("images/player/player_jungle_jump.png", 70, 122, 10);
	Animated player_barrelroll("images/player/player_jungle_barrelroll.png", 140, 122, 6);
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
		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
		//Draw the Screen
		
		surface.fill(BLACK);
		player_run.step();
		player_run.on_screen_rect.x = 0; //set screen pos like this
		player_run.on_screen_rect.y = 0;
		player_jump.step();
		player_jump.on_screen_rect.x = 0;
		player_jump.on_screen_rect.y = 125;
		player_barrelroll.step();
		
		surface.put_image(player_run);
		surface.put_image(player_jump);
		surface.put_image(player_barrelroll, 75, 0); //or set screen pos like this
		
		surface.flip();
		SDL_Delay(10);
		
		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////
	}
	return 0;
}
