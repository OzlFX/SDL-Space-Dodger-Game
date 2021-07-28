#ifndef _CGAMEOBJECT_H_
#define _CGAMEOBJECT_H_

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

class cGameObject
{
private:
	bool hasCollided(cGameObject* _object); //Checks for collision with another object

protected:
	Mix_Chunk * explosionEffect = Mix_LoadWAV("explosion.wav"); //Sets the explosion sound

	SDL_Texture* Texture; //Creates a new texture to display the image with
	SDL_Surface* surfaceLoader; //Creates a new surface for the image

	SDL_Renderer* renderer; //Creates a local renderer

	SDL_Rect _pos; //Creates a source rect
public:
	cGameObject(SDL_Renderer* _renderer, const char* _file, int _x, int _y, int _w, int _h); //sets the default constructor for the game objects
	SDL_Texture* loadTexture(SDL_Renderer* _renderer, const char* _img, int _x, int _y, int _w, int _h); //Loads the image and converts it to a texture

	//Gets the dimensions of the object
	int getX() { return _pos.x; }
	int getY() { return _pos.y; }
	int getW() { return _pos.w; }
	int getH() { return _pos.h; }

	SDL_Rect& getDimensions(); //Gets the image dimensions for the image

	//Set the image position and dimensions
	void setX(int _x) { _pos.x = _x; }
	void setY(int _y) { _pos.y = _y; }
	void setW(int _w) { _pos.w = _w; }
	void setH(int _h) { _pos.h = _h; }

	void Draw(SDL_Renderer* _renderer); //draw function

	void reset(const char* _file); //Resets the textures

	bool onCollide(cGameObject* _object); //Checks for collision

	~cGameObject();
};

#endif