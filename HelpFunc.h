#ifndef __HELP_FUNC__
#define __HELP_FUNC__
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <unordered_set>
#include <queue>

const int width = 1320;
const int hight = 760;
const int blockSize = 40;

const char Wall = 'B';
const char Passage = 'P';
const char Plr = 'Q';
const char Enm = 'O';
const char Obj = 'V';



enum TEXTURES
{
	DIRT,
	BG,
	PLAYER,
	EMERALD,
	ENEMY1,
	WIN,
	LOSE
};

struct Textures
{
	Textures(std::string _textures, SDL_Renderer* renderer) {
		std::ifstream txt(_textures);
		if (!txt.good())
		{
			std::cout << "Couldnt open file: " << _textures << '\n';
		}
		loadTextures(txt, renderer);
	}

	void loadTextures(std::ifstream & in, SDL_Renderer* renderer)
	{
		char row[32];
		while (in.getline(row, 31))
		{
			textures.push_back(IMG_LoadTexture(renderer, row));
		}
		in.clear();
		in.close();
	}

	SDL_Texture* operator[](size_t i) {
		return textures[i];
	}

	std::vector<SDL_Texture*> textures;
};



struct Position
{
	Position(int _x = 1 * blockSize, int _y = 1 * blockSize) :x(_x), y(_y){}
	//Position(Position& other) { x = other.x, y = other.y; }
	//Position & operator =(Position& other) { x = other.x, y = other.y; }
	int x;
	int y;
};


struct Path
{
	Path(Position _pos, Path* _parent = nullptr) :pos(_pos), parent(_parent) {}
	Position pos;
	Path* parent;
};

#endif // !__HELP_FUNC__

