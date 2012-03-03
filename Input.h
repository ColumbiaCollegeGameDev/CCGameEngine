#ifndef INPUT_H
#define INPUT_H

#include "SDL.h"

class Mouse_Input
{
public:
	Mouse_Input()
		: mouse_x(0), mouse_y(0), left_down(0), left_pressed(0), left_released(0), middle_down(0), middle_pressed(0), middle_released(0),
		  right_down(0), right_pressed(0), right_released(0), wheel_up(0), wheel_down(0)
	{}
	
	void update(int);
	
	int mouse_x, mouse_y;
	bool left_down, left_pressed, left_released;
	bool middle_down, middle_pressed, middle_released;
	bool right_down, right_pressed, right_released;
	bool wheel_up, wheel_down;
private:
};

class Keyboard
{
public:
	void update();
};

#endif
