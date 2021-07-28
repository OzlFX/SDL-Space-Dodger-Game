#include "cGameObject.h"

//Base constructor
cGameObject::cGameObject(SDL_Renderer* _renderer, const char* _file, int _x, int _y, int _w, int _h)
{
	renderer = _renderer;
	loadTexture(_renderer, _file, _x, _y, _w, _h);
}

void cGameObject::Draw(SDL_Renderer * _renderer)
{
	if (Texture)
	{
		SDL_RenderCopy(_renderer, Texture, NULL, &_pos);
	}
	else
	{
		std::cout << "Could not draw texture " << Texture << "! " << SDL_GetError();
	}
}

void cGameObject::reset(const char* _file)
{
	this->loadTexture(renderer, _file, _pos.x, _pos.y, _pos.w, _pos.h);
}

bool cGameObject::hasCollided(cGameObject * _object)
{
	return SDL_HasIntersection(&_pos, &_object->getDimensions());
}

SDL_Texture* cGameObject::loadTexture(SDL_Renderer* _renderer, const char* _img, int _x, int _y, int _w, int _h)
{
	//Load image file path to the SDL_Surface
	surfaceLoader = SDL_LoadBMP(_img);
	//Check if loading was successful
	if (surfaceLoader == NULL)
	{
		std::cout << "Error: Unable to load image " << _img << "! " << std::endl << SDL_GetError() << std::endl;
	}
	else
	{
		//Convert image to texture
		Texture = SDL_CreateTextureFromSurface(_renderer, surfaceLoader);
		//Check if conversion was successful
		if (Texture == NULL)
		{
			std::cout << "Error: Unable to create texture from SDL_Surface for image " << _img << "! " << std::endl << SDL_GetError() << std::endl;
		}
		//Free the loaded surface
		SDL_FreeSurface(surfaceLoader);

		setX(_x);
		setY(_y);
		setW(_w);
		setH(_h);
		getDimensions();
	}

	return Texture;
}

SDL_Rect& cGameObject::getDimensions()
{
	return _pos;
}

//Collision function
bool cGameObject::onCollide(cGameObject * _object)
{
	if (this->hasCollided(_object))
	{
		this->loadTexture(renderer, "explosion.bmp", _pos.x, _pos.y, _pos.w, _pos.h);
		Mix_PlayChannel(-1, explosionEffect, 0);
		return true;
	}
	return false;
}

//destructor
cGameObject::~cGameObject()
{
	SDL_DestroyTexture(Texture);
}
