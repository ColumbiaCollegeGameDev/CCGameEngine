#ifndef INPUT_H
#define INPUT_H

#include <bitset>
#include "SDL.h"

class Mouse_Input
{
public:
	Mouse_Input()
		: mouse_x(0), mouse_y(0), left_down(0), left_pressed(0), left_released(0), middle_down(0), middle_pressed(0), middle_released(0),
		  right_down(0), right_pressed(0), right_released(0), wheel_up(0), wheel_down(0)
	{}
	
	void reset();
	void pressed(Uint8);
	void released(Uint8);
	
	int mouse_x, mouse_y;
	bool left_down, left_pressed, left_released;
	bool middle_down, middle_pressed, middle_released;
	bool right_down, right_pressed, right_released;
	bool wheel_up, wheel_down;
};

class Keyboard
{
public:
	Keyboard()
		: keys_pressed(0), keys_down(0), keys_released(0)
	{}
	void reset();
	void pressed(SDLKey&);
	void released(SDLKey&);
	bool key_pressed(int); //takes SDL Keys like SDLK_a for the letter a
	bool key_down(int);
	bool key_released(int);
private:
	std::bitset<256> keys_pressed;
	std::bitset<256> keys_down;
	std::bitset<256> keys_released;
};

#endif
