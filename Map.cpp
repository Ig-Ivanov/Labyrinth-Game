#include "Map.h"
#include <string>


Map::Map(std::string gameMap, std::string _textures, SDL_Renderer* renderer)
	:rend(renderer)
	,textures(_textures,renderer)
	,player(Position(),textures[PLAYER])
{
	std::ifstream map(gameMap);
	if (!map.good())
	{
		std::cout << "Couldnt open file: " << gameMap << '\n';
	}
	createMap(map);
}

Map::~Map()
{
}

void Map::createMap(std::ifstream & in)
{
	std::string row;
	while (std::getline(in,row)) {
		map.push_back(row);
	}
	in.clear();
	in.close();
}

void Map::createBonusMap()
{
	for (size_t i = 0; i < hight / blockSize; i++)
	{
		for (size_t j = 0; j < width / blockSize ; j++)
		{
			map[i][j] = Wall;
		}
	}
	printMap(rend);
	srand(time(NULL));
	std::vector<std::pair<int, int>> q;
	std::pair<int, int> curr(1, 1);
	q.push_back(curr);
	std::pair<int, int> next;
	SDL_Rect rect{ 0,0,blockSize,blockSize };
	while (!q.empty())
	{
		int random = rand() % q.size();
		curr = q[random];
		q.erase(q.begin() + random);

		if (map[curr.first][curr.second] == Wall) {
			map[curr.first][curr.second] = Passage;
			rect.y =curr.first * blockSize;
			rect.x = curr.second * blockSize;
			SDL_RenderCopy(rend, textures[BG], 0, &rect);
			SDL_RenderPresent(rend);
			//SDL_Delay(3000 / 40);
			conect(curr);
			//printMap(rend);
			if (withinRange(curr.first + 2, curr.second) && map[curr.first + 2][curr.second] == Wall)
			{
				next = curr;
				next.first += 2;
				q.push_back(next);
			}
			if (withinRange(curr.first - 2, curr.second) && map[curr.first - 2][curr.second] == Wall) {
				next = curr;
				next.first -= 2;
				q.push_back(next);
			}
			if (withinRange(curr.first, curr.second + 2) && map[curr.first][curr.second + 2] == Wall)
			{
				next = curr;
				next.second += 2;
				q.push_back(next);
			}
			if (withinRange(curr.first, curr.second - 2) && map[curr.first][curr.second - 2] == Wall) {
				next = curr;
				next.second -= 2;
				q.push_back(next);
			}
		}
		//printMap(rend);
	}
	enemyStartingPoint.y = curr.first * blockSize;
	enemyStartingPoint.x = curr.second * blockSize;
	setEmeralds();
	SDL_RenderPresent(rend);
}

bool Map::withinRange(int x, int y)
{
	return (x > 0 && x < (hight / blockSize) && y > 0 && y < (width / blockSize));
}

void Map::conect(std::pair<int, int> curr)
{
	std::vector<std::pair<int, int>> temp;
	std::pair<int, int> next;
	if (withinRange(curr.first + 2,curr.second) && map[curr.first + 2][curr.second] == Passage) {
		next = curr;
		next.first += 1;
		temp.push_back(next);
	}
	if (withinRange(curr.first - 2, curr.second) && map[curr.first - 2][curr.second] == Passage) {
		next = curr;
		next.first -= 1;
		temp.push_back(next);
	}

	if (withinRange(curr.first, curr.second + 2) && map[curr.first][curr.second + 2] == Passage) {
		next = curr;
		next.second += 1;
		temp.push_back(next);
	}

	if (withinRange(curr.first, curr.second - 2) && map[curr.first ][curr.second - 2] == Passage) {
		next = curr;
		next.second -= 1;
		temp.push_back(next);
	}

	if (temp.size() != 0) {
		next = temp[rand() % temp.size()];
		map[next.first][next.second] = Passage;
		SDL_Rect rect{ 0,0,blockSize,blockSize };
		rect.y = next.first * blockSize;
		rect.x = next.second * blockSize;
		SDL_RenderCopy(rend, textures[BG], 0, &rect);
		SDL_RenderPresent(rend);
	}
}

void Map::printMap(SDL_Renderer* renderer)
{
	SDL_RenderClear(renderer);
	SDL_Rect rect{ 0,0,blockSize,blockSize };
	SDL_RenderCopy(renderer,textures[DIRT],0,&rect);
	SDL_RenderPresent(renderer);
	for (size_t i = 0; i < hight / blockSize ; i++)
	{
		rect.y = i*blockSize;
		rect.x = 0;
		for (size_t j = 0; j < width / blockSize; j++)
		{
			rect.x = j*blockSize;
			if (map[i][j] == Wall) {
				SDL_RenderCopy(renderer, textures[DIRT], 0, &rect);
			}
			else if (map[i][j] == Passage) {
				SDL_RenderCopy(renderer, textures[BG], 0, &rect);
			}
		}
	}
	
}

bool Map::updateMap(Position pos)
{
	player.draw(rend);
	player.drawBG(rend, textures[BG]);
	player.changePos(pos);
	player.draw(rend);
	if ((rand() % 200 == 1)  && enemies.size() <=5)
	{
		createEnemy();
		enemies[enemies.size() - 1].changeRep(map);
	}

	//if(enemies.size() >= 1 ) player.BFSPLR(map, enemies);
	int length = enemies.size();
	for (size_t i = 0; i < length; i++)
	{
		enemies[i].drawBG(rend, textures[BG]);
		enemies[i].getPath(map);
		enemies[i].changePos(enemies[i].getMove());
		Position enm = enemies[i].changeRep(map);
		if (enm.x != -1 && enm.y != -1) {
			if (checkEnemyColl(enm))
			{
				enemies[i].updateEnemy(map);
				enemies.erase(enemies.begin() + i);
				--length;
				continue;
			}
		}
		enemies[i].draw(rend);
	}
	Position temp = player.changeRep(map);
	if (temp.x != -1 && temp.y != -1)
	{
		checkPlrColl(temp);
	}
	if (emeralds.size() == 0)
	{
		SDL_RenderCopy(rend, textures[WIN], NULL, NULL);
		SDL_RenderPresent(rend);
		return false;
	}
	if (player.getLive() == 0) {
		SDL_RenderCopy(rend, textures[LOSE], NULL, NULL);
		SDL_RenderPresent(rend);
		SDL_Delay(1000);
		return false;
	}
	SDL_RenderPresent(rend);
	return true;
}

bool Map::checkPlrColl(Position pos)
{
	int length = enemies.size();
	Position temp;
	for (size_t i = 0; i <  length; i++)
	{
		temp = enemies[i].Center();
		if (pos.x == (temp.x / blockSize) && pos.y == (temp.y / blockSize))
		{
			enemies[i].updateEnemy(map);
			enemies.erase(enemies.begin() + i);
			if (player.loseLive() == 0) return true;
			return false;
		}
	}

	length = emeralds.size();
	for (size_t i = 0; i < length; i++)
	{
		temp = emeralds[i].ObjCenter();
		if (pos.x == (temp.x / blockSize) && pos.y == (temp.y / blockSize))
		{
			player.updateScore(emeralds[i].getScore());
			emeralds[i].updateObj(map);
			emeralds[i].drawObjBG(rend,textures[BG]);
			emeralds.erase(emeralds.begin() + i);
			return false;
		}
	}
	
}

void Map::setEmeralds()
{
	int temp = rand() % 10 + 1;
	for (size_t i = 0; i < temp; i++)
	{
		Position pos((rand() % width - (blockSize * 2)), (rand() % hight - (blockSize * 2)));
		if (pos.x > 0 && pos.y > 0) {
			if ((pos.x % blockSize) != 0)
			{
				pos.x += blockSize - (pos.x % blockSize);
			}
			if ((pos.y % blockSize) != 0)
			{
				pos.y += blockSize - (pos.y % blockSize);
			}
			Emeralds temp(pos, textures[EMERALD]);
			emeralds.push_back(temp);
			emeralds.back().changeObjectiveRep(map);
			emeralds.back().drawObjective(rend);
		}
	}
}

void Map::createEnemy()
{
	enemies.push_back(Enemy(enemyStartingPoint, textures[ENEMY1], Enm));
}

bool Map::checkEnemyColl(Position pos)
{
	Position temp = player.Center();
	if (pos.x == temp.x / blockSize && pos.y == temp.y / blockSize) {
		player.loseLive();
		return true;
	}
	return false;
}
