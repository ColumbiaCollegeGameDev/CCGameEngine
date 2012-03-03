#include "Input.h"

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//Mouse_Input

void Mouse_Input::update(int n)
{
	//You should call this at the beginning of the game loop *
	
	//reset vars
	bool l_down = left_down, m_down = middle_down, r_down = right_down;//these are used to determine if the buttons are just pressed
	
	left_down = 0; middle_down = 0; right_down = 0; wheel_up = 0; wheel_down = 0;
	left_pressed = 0; middle_pressed = 0; right_pressed = 0;
	left_released = 0; middle_released = 0; right_released = 0;
	
	//check for updates
	switch(SDL_GetMouseState(&mouse_x, &mouse_y))
	{
	case SDL_BUTTON(1):
		if (!l_down) left_pressed = 1;
		left_down = 1; 
		break;
	case SDL_BUTTON(2): 
		if (!m_down) middle_pressed = 1;
		middle_down = 1; 
		break;
	case SDL_BUTTON(3): 
		if (!r_down) right_pressed = 1;
		right_down = 1; 
		break;
	case SDL_BUTTON(4): 
		wheel_up = 1; 
		break;
	case SDL_BUTTON(5): 
		wheel_down = 1;
	}
	
	//check for releases
	if (l_down && !left_down) left_released = 1;
	if (m_down && !middle_down) middle_released = 1;
	if (r_down && !right_down) right_released = 1;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//Keyboard

void Keyboard::update()
{
	
}
