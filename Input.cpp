#include "Input.h"
#include <iostream>
#include <cstdlib>

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//Mouse_Input

void Mouse_Input::reset()
{
	left_pressed = 0; middle_pressed = 0; right_pressed = 0;
	left_released = 0; middle_released = 0; right_released = 0;
	wheel_up = 0; wheel_down = 0;
	mouse_dx = 0; mouse_dy = 0;
}

void Mouse_Input::pressed(Uint8 button)
{
	switch(button)
	{
	case SDL_BUTTON_LEFT:
		left_pressed = 1;
		left_down = 1; 
		break;
	case SDL_BUTTON_MIDDLE: 
		middle_pressed = 1;
		middle_down = 1; 
		break;
	case SDL_BUTTON_RIGHT: 
		right_pressed = 1;
		right_down = 1; 
		break;
	case SDL_BUTTON_WHEELUP: 
		wheel_up = 1;
		break;
	case SDL_BUTTON_WHEELDOWN: 
		wheel_down = 1;
	}
}

void Mouse_Input::released(Uint8 button)
{
	switch(button)
	{
	case SDL_BUTTON_LEFT:
		left_released = 1;
		left_down = 0; 
		break;
	case SDL_BUTTON_MIDDLE: 
		middle_released = 1;
		middle_down = 0; 
		break;
	case SDL_BUTTON_RIGHT: 
		right_released = 1;
		right_down = 0; 
		break;
	}
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//Keyboard

void Keyboard::reset()
{
	keys_pressed.reset();
	keys_released.reset();
}

void Keyboard::pressed(SDLKey &keys)
{
	if (int(keys) >= AMOUNT_OF_KEYS) return;
	keys_pressed.set(keys, 1);
	keys_down.set(keys, 1);
}

void Keyboard::released(SDLKey &keys)
{
	if (int(keys) >= AMOUNT_OF_KEYS) return;
	keys_released.set(keys, 1);
	keys_down.set(keys, 0);
}

bool Keyboard::key_pressed(int index) const
{
	if (index >= AMOUNT_OF_KEYS) return 0;
	return keys_pressed.test(index);
}

bool Keyboard::key_down(int index) const
{
	if (index >= AMOUNT_OF_KEYS) return 0;
	return keys_down.test(index);
}

bool Keyboard::key_released(int index) const
{
	if (index >= AMOUNT_OF_KEYS) return 0;
	return keys_released.test(index);
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//Events

int Events::update()
{
	//return_ handles anything needing to be communicated with the main method.
	//-1 = window close button pressed
	// 0 = nothing;
	int return_ = 0;
	
	mouse.reset();
	keyboard.reset();
	
	while (SDL_PollEvent(&event))
			switch(event.type)
			{
			case SDL_QUIT: return_ = -1; break;
			case SDL_MOUSEBUTTONDOWN:
			        mouse.pressed(event.button.button);
				break;
			case SDL_MOUSEBUTTONUP:
				mouse.released(event.button.button);
				break;
			case SDL_MOUSEMOTION:
				mouse.mouse_dx = event.motion.xrel;
				mouse.mouse_dy = event.motion.yrel;
				mouse.mouse_x = event.motion.x;
				mouse.mouse_y = event.motion.y;
				break;
			case SDL_KEYDOWN: 
				keyboard.pressed(event.key.keysym.sym);
				break;
			case SDL_KEYUP: 
				keyboard.released(event.key.keysym.sym);
				break;
			}
			
	return return_;
}
