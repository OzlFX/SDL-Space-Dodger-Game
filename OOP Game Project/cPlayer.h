#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "cGameObject.h"
class cPlayer :
	public cGameObject //Player class inherits from game object
{
public:
	cPlayer(SDL_Renderer* _renderer, const char* _file, int _x, int _y, int _w, int _h); //Class constructor inheirits from base class

	void Move(SDL_Event _Event);// Moves the player based on user input

	~cPlayer();
};

#endif