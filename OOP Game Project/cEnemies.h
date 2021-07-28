#ifndef _CENEMIES_H_
#define _CENEMIES_H_

#include "cGameObject.h"
#include <time.h>

class cEnemies :
	public cGameObject //Enemies class inherits from game object
{
public:
	cEnemies(SDL_Renderer* _renderer, const char* _file, int _x, int _y, int _w, int _h); //Class constructor inheirits from base class

	void Spawn(); //Spawns the enemies at a new location when created
	void Move(float _moveSpeed); //Moves the enemies

	void reSpawn(); //Respawns the enemies

	void outOfBounds(); //Checks to see if the object is out of the screen

	~cEnemies();
};

#endif