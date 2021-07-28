#ifndef _CPROGRAM_H_
#define _CPROGRAM_H_

#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include <vector>

#include "cGameObject.h"
#include "cPlayer.h"
#include "cEnemies.h"

class cProgram
{
private:
	//Creates the window and renderer for the game
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event events;

	Mix_Music* bckgMusic; //Sets the background music for the game

	/* Functions */
	bool Init(); //Define initialise function
	SDL_Window* createWindow(); //Define window create function
	SDL_Renderer* createRenderer(); //Define renderer create function
	void setUpMusic(); //Define music set up function
	void loadMusic(); //Define music loader
	
	const Uint8* states = SDL_GetKeyboardState(NULL); //Setup keyboard state system

	void keyboardStates(); //Define keyboard states

	void createObjects(); //Define object creation function
	void drawObjects(); //Define object draw function

	void Run(); //Define run function

	void Menu(); //Define Menu function
	void Game(); //Define Game function

	void CleanUp(); //Define clean-up function

	bool running = false; //Set running to true to control the program being open or not
	bool initComplete = false;

	//Sets up the window size
	int winW = 1200;
	int winH = 800;

	//Program's check parameters
	bool menu = true;
	bool game, help, gameWin, gameLose = false;

	//Sets the player's start position
	int playerX = winW / 2;
	int playerY = winH - 64;

	int mouseX, mouseY; //Sets up the mouse position variables

	//Sets up a frame counter
	int count = 0;

	//Set up score;
	int max_score = 350;

	std::shared_ptr<cPlayer> player; //Set up shared pointer to the player

	std::vector<std::shared_ptr<cGameObject>> bckImages; //Create a vector of shared pointers for game object which contains the background images
	std::vector<std::shared_ptr<cGameObject>> buttons; //Create a vector of shared pointers for game object which contains all buttons
	std::vector<std::shared_ptr<cEnemies>> pirates; //Create a vector of shared pointers for the pirate enemies

public:
	cProgram();

	void Update(); //Define update loop function

	~cProgram();
};

#endif