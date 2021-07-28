#include "cEnemies.h"

//Constructor that inheirits from cGameObject
cEnemies::cEnemies(SDL_Renderer* _renderer, const char* _file, int _x, int _y, int _w, int _h) : cGameObject(_renderer, _file, _x, -70, _w, _h)
{
}

//Spawns the object
void cEnemies::Spawn()
{
	//srand(time(NULL));
	int _x = rand() % 1136;
	setX(_x);
}

//Moves the object
void cEnemies::Move(float _moveSpeed)
{
	int _y = getY();
	_y += _moveSpeed;
	setY(_y);
}

void cEnemies::reSpawn()
{
	int _y = -70;
	setY(_y);
	Spawn();
}

//Checks if out of bounds
void cEnemies::outOfBounds()
{
	if (getY() > 800)
	{
		reSpawn();
	}
}

cEnemies::~cEnemies()
{
}
