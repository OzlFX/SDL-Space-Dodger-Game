#include "cProgram.h"

cProgram::cProgram()
{
	running = true;

	initComplete = Init(); //Set up the game
	//Checks if SDL has been initialised
	if (Init() == false)
	{
		std::cout << "Failed to initialise SDL!" << std::endl << SDL_GetError() << " !" << std::endl;
	}
}

//Init all game features
bool cProgram::Init()
{
	//Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		//if SDL fails to initialises, an error is returned to the console and closes the game
		std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to initialize SDL!" << std::endl;
		return false;
	}

	//Set up the window and renderer
	window = createWindow();
	renderer = createRenderer();
	setUpMusic(); //Set up the music
	loadMusic(); //load the music

	return true;
}

//Create the window
SDL_Window* cProgram::createWindow()
{
	//Creates a new window
	SDL_Window* _window = SDL_CreateWindow("Space Dodger", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, SDL_WINDOW_OPENGL);

	//Checks to see if the window has been created and initialised
	if (_window == NULL)
	{
		//if the window doesnt exist, an error is returned to the console and closes the game
		std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to create Window!" << std::endl;
		return false;
	}

	return _window;
}

//Create the renderer
SDL_Renderer* cProgram::createRenderer()
{
	//Creates the renderer
	SDL_Renderer* _renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//Checks to see if the renderer has been created and initialised
	if (_renderer == NULL)
	{
		//if the renderer doesnt exist, an error is returned to the console
		std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to create Renderer!" << std::endl;
		//The window is destroyed, SDL is closed and closes the game
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	return _renderer;
}

//Set up music for usage in the game
void cProgram::setUpMusic()
{
	//Checks to see if the mixer has been initialised
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == NULL)
	{
		//if the mixer can't be initialised, an error is returned to the console
		std::cout << "ERROR: " << SDL_GetError() << std::endl << "unable to initialise the mixer!" << std::endl;
	}
}

//Load the music
void cProgram::loadMusic()
{
	bckgMusic = Mix_LoadMUS("bckgMusic.wav"); //Loads the background music

	if (bckgMusic == NULL)
	{
		std::cout << "Error loading music!" << std::endl;
	}
}

//Create all objects in the game
void cProgram::createObjects()
{
	/* Creation of all game objects */
	//Set up background images
	if (menu)
	{
		bckImages.push_back(std::shared_ptr<cGameObject>(new cGameObject(renderer, "mainMenuBkg.bmp", 0, 0, winW, winH))); //Main Menu background image
		//cGameObject * mainMenu = new cGameObject(renderer, "mainMenuBkg.bmp", 0, 0, winW, winH); //Old define
		//Sets up the menu buttons system
		//Load the images with specified definition values
		buttons.push_back(std::shared_ptr<cGameObject>(new cGameObject(renderer, "StartButton.bmp", winW / 2 - 64, winH / 2 - 50, 128, 32)));
		buttons.push_back(std::shared_ptr<cGameObject>(new cGameObject(renderer, "HelpButton.bmp", winW / 2 - 64, winH / 2, 128, 32)));
		buttons.push_back(std::shared_ptr<cGameObject>(new cGameObject(renderer, "QuitButton.bmp", winW / 2 - 64, winH / 2 + 50, 128, 32)));
		//cGameObject* startButton = new cGameObject(renderer, "StartButton.bmp", winW / 2 - 64, winH / 2 - 50, 128, 32);
		//cGameObject* helpButton = new cGameObject(renderer, "HelpButton.bmp", winW / 2 - 64, winH / 2, 128, 32);
		//cGameObject* quitButton = new cGameObject(renderer, "QuitButton.bmp", winW / 2 - 64, winH / 2 + 50, 128, 32);
	}
	else
	{
		//Clear vector of objects for the menu
		bckImages.clear();
		buttons.clear();
	}

	if (game)
	{
		bckImages.push_back(std::shared_ptr<cGameObject>(new cGameObject(renderer, "gameBkg.bmp", 0, 0, winW, winH))); //Main game background image
		//Set up the player
		player = std::shared_ptr<cPlayer>(new cPlayer(renderer, "playerShip.bmp", playerX, playerY, 64, 64));

		int posX = 10;
		//Set up all enemies
		for (int i = 0; i < 10; i++)
		{
			pirates.push_back(std::shared_ptr<cEnemies>(new cEnemies(renderer, "pirateShip.bmp", posX, -70, 64, 64)));
			posX += 84;
		}
	}
	else
	{
		pirates.clear(); //Clear pirates
	}
}

//Draw all the objects
void cProgram::drawObjects()
{

}

//Check to see if the window has been closed via the 'X' button
void cProgram::Run()
{
	events = { 0 };

	while (SDL_PollEvent(&events))
	{
		if (events.type == SDL_QUIT)
		{
			running = false;
		}
	}
}

//Check escape to close game
void cProgram::keyboardStates()
{
	//Check to see if the escape key has been pressed
	if (states[SDL_SCANCODE_ESCAPE])
	{
		running = false;
	}
}

//Main update loop
void cProgram::Update()
{
	//Run the music
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(bckgMusic, 1);
	}

	while (running)
	{
		Run(); //Check to see if the exit button has been pressed
	}
}

//Clears all objects and SDL, freeing memory before the game is closed
void cProgram::CleanUp()
{
	//Clear Audio
	Mix_FreeMusic(bckgMusic);
	Mix_CloseAudio();
	//Destroy the renderer
	SDL_DestroyRenderer(renderer);
	//Destroy the window
	SDL_DestroyWindow(window);
	//Quit SDL
	SDL_Quit();
}

//Menu function
void cProgram::Menu()
{

	while (menu)
	{
		/* Draw the objects on the screen */
		//Sets the background colour of the window
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xA0, 0x0F, 0xFF);
		//Empties the render ready to draw a new object
		SDL_RenderClear(renderer);
		//Renders the background image
		bckImages.at(0)->Draw(renderer);

		//Draw the buttons
		for (int i = 0; i < buttons.size(); i++)
		{
			buttons.at(i)->Draw(renderer);
		}

		//Update the screen
		SDL_RenderPresent(renderer);

		//Checks to see if there are any pending events and passes them to the game event function (will do this until all pending events have been passed into the game event function)
		while (SDL_PollEvent(&events))
		{
			//Get mouse pos
			SDL_GetMouseState(&mouseX, &mouseY);
			//Checks for left mouse button input
			if (events.button.button == SDL_BUTTON_LEFT)
			{
				if ((mouseX > (winW / 2 - 64)) && (mouseY > (winH / 2 - 50)) && (mouseX < ((winW / 2 - 64) + 128)) && (mouseY < ((winH / 2 - 50) + 32)))
				{
					std::cout << "pressed mouse left button on start" << std::endl;
					menu = false;
					game = true;
				}
				if ((mouseX > (winW / 2 - 64)) && (mouseY > (winH / 2)) && (mouseX < ((winW / 2 - 64) + 128)) && (mouseY < ((winH / 2) + 32)))
				{
					std::cout << "pressed mouse left button on help" << std::endl;
					help = true;
				}
				if ((mouseX > (winW / 2 - 64)) && (mouseY > (winH / 2 + 50)) && (mouseX < ((winW / 2 - 64) + 128)) && (mouseY < ((winH / 2 + 50) + 32)))
				{
					std::cout << "pressed mouse left button on exit" << std::endl;
					menu = false;
					running = false;
				}
			}
			if (help)
			{
				//Loads the Instructions 'screen'
				cGameObject* instructions = new cGameObject(renderer, "instructionsImg.bmp", 200, 100, 800, 600);

				instructions->Draw(renderer);
				SDL_RenderPresent(renderer);
				SDL_Delay(6000);
				delete instructions;
				help = false;
			}
		}
	}
}

//Game function
void GameLoop(SDL_Event* _Event)
{
	//Set up the assets for the game
	cGameObject * gameBkg = new cGameObject(renderer, "gameBkg.bmp", 0, 0, winW, winH);

	cGameObject* scoreSystem = new cGameObject(renderer, "bullet.bmp", 12, 0, 24, 0); //Creates the scoring system

	//Game over assets
	cGameObject* gameWin = new cGameObject(renderer, "Win.bmp", winW / 2 - 64, winH / 2 - 50, 128, 32);
	cGameObject* gameLose = new cGameObject(renderer, "Lose.bmp", winW / 2 - 64, winH / 2 - 50, 128, 32);

	//Spawn enemies
	Pirate->Spawn();

	while (game)
	{
		float score = count / 60; //update the score

		while (SDL_PollEvent(_Event))
		{
			//Checks for the 'Quit' event in the game loop
			if (_Event->type == SDL_QUIT)
			{
				game = false;
				Running = false;
			}
			//Moves the player
			Player->Move(*_Event);
		}

		//Move the enemies
		Pirate->Move(1.0);

		//Check for collision
		if (Player->onCollide(Pirate))
		{
			Pirate->onCollide(Player);

			//Update the draw
			Pirate->Draw(renderer);
			Player->Draw(renderer);
			//Draw lose screen
			gameLose->Draw(renderer);
			//Update the screen
			SDL_RenderPresent(renderer);

			//Wait 5 seconds and then return to the menu
			SDL_Delay(5000);
			count = 0;
			Pirate->reSpawn();
			Pirate->reset("pirateShip.bmp");
			Player->reset("playerShip.bmp");
			game = false;
			menu = true;
			MenuLoop(_Event);
		}

		//Update the score
		scoreSystem->setH(score);
		//check if the player has won and draw the win screen
		if (score >= max_score)
		{
			//Draw win screen
			gameWin->Draw(renderer);
			//Update the screen
			SDL_RenderPresent(renderer);
			SDL_Delay(5000);
			count = 0;
			game = false;
			menu = true;
			MenuLoop(_Event);
		}

		//Check to see if they are out of bounds
		Pirate->outOfBounds();

		//Sets the background colour of the window
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xA0, 0x0F, 0xFF);
		//Empties the render ready to draw a new object
		SDL_RenderClear(renderer);
		//Renders the background image
		gameBkg->Draw(renderer);
		//Render game objects
		Player->Draw(renderer);
		Pirate->Draw(renderer);

		//Draw the score
		scoreSystem->Draw(renderer);

		//Update the screen
		SDL_RenderPresent(renderer);

		count++;
	}
}

cProgram::~cProgram()
{
	CleanUp(); //Clean up the game data
}
