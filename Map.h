#ifndef __MAP__
#define __MAP__
#include <iostream>
#include <vector>
#include "Player.h"
#include "Enemies.h"
#include "Bags.h"
#include "Emeralds.h"
#include <utility>
#include <stdlib.h> 
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>


class Map
{
public:
	Map(std::string gameMap,std::string textures,SDL_Renderer* renderer);
	~Map();

	void createMap(std::ifstream& in);
	void createBonusMap();
	void printMap(SDL_Renderer*);
	bool updateMap(Position pos);
	bool checkPlrColl(Position pos);
	void setEmeralds();
	void createEnemy();
	bool checkEnemyColl(Position pos);

private:
	bool withinRange(int x, int y);
	void conect(std::pair<int, int>);
private:
	std::vector<std::string> map;
	Textures textures;
	SDL_Renderer* rend;
	Player player;
	std::vector<Enemy> enemies;
	std::vector<Emeralds> emeralds;
	Position enemyStartingPoint;
};
#endif // !__MAP__
