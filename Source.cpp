#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Map.h"



int main(int argc,char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window * window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, hight, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	
	Map MP("Map1.txt","Images.txt",renderer);
	MP.createBonusMap();
	//MP.printMap(renderer);
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	Position pos;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&e);
		//User requests quit
		if (e.type == SDL_QUIT)
		{
			quit = true;
		}
		else
		{
			pos.x = 0;
			pos.y = 0;

			if (keystates[UP])
				pos.y -= 5;

			else if (keystates[DOWN])
				pos.y += 5;

			else if (keystates[LEFT])
				pos.x -= 5;

			else if (keystates[RIGHT])
				pos.x += 5;

			if (!MP.updateMap(pos)) return 0;
		}
		SDL_Delay(1000/40);
	}

}