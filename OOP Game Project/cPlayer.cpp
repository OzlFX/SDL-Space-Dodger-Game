#include "cPlayer.h"

cPlayer::cPlayer(SDL_Renderer* _renderer, const char* _file, int _x, int _y, int _w, int _h): cGameObject(_renderer, _file, _x, _y, _w, _h)
{
}

//Move function
void cPlayer::Move(SDL_Event _Event)
{
	int _x = getX();

	//Checks for the 'a' key being pressed in the game loop
	if (_Event.key.keysym.sym == SDLK_a)
	{
		if (getX() > 0)
		{
			_x -= 80;
			setX(_x);
		}
	}
	//Checks for the 's' key to be pressed in the game loop
	if (_Event.key.keysym.sym == SDLK_s)
	{
		if (getX() < 1136)
		{
			_x += 80;
			setX(_x);
		}
	}
}

cPlayer::~cPlayer()
{
}
