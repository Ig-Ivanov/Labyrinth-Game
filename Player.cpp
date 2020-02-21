#include "Player.h"

const int yPos[4] = { -1, 1 , 0 , 0 };
const int xPos[4] = {  0, 0 , -1 , 1 };


Player::~Player()
{

}

Position Player::changeRep(std::vector<std::string> & map)
{
	Position curr((Center().x / blockSize), (Center().y / blockSize));
	if ((curr.x > 0) && (curr.y > 0) && (curr.x <= (width / blockSize) - 2) && (curr.y <= (hight / blockSize) - 2))
		if (map[curr.y][curr.x] != rep)
		{
			if (map[curr.y][curr.x] == Wall || map[curr.y][curr.x] == Passage) {
				map[curr.y][curr.x] = rep;
				if (map[curr.y - 1][curr.x] == rep) map[curr.y - 1][curr.x] = Passage;
				if (map[curr.y + 1][curr.x] == rep) map[curr.y + 1][curr.x] = Passage;
				if (map[curr.y][curr.x - 1] == rep) map[curr.y][curr.x - 1] = Passage;
				if (map[curr.y][curr.x + 1] == rep) map[curr.y][curr.x + 1] = Passage;
				
			}
			else
			{
				return curr;
			}
		}
	return Position(-1, -1);
}

void Player::BFSPLR(std::vector<std::string>& map, std::vector<Enemy>& enemies)
{
	bool** visited = new bool*[hight / blockSize];
	for (size_t i = 0; i < hight / blockSize; i++)
	{
		visited[i] = new bool[width / blockSize];
	}

	for (size_t i = 0; i < hight / blockSize; i++)
	{
		for (size_t j = 0; j < width / blockSize; j++)
		{
			visited[i][j] = false;
		}
	}
	std::queue<Position> q;
	Position curr;
	curr.x = rect.x;
	curr.y = rect.y;
	curr.x /= blockSize;
	curr.y /= blockSize;
	q.push(curr);
	//Position prior = curr;
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		if (map[curr.y][curr.x] != Passage)continue;
		for (size_t i = 0; i < 4; i++)
		{
			int length = enemies.size();
			if (inRangePLR((curr.y + yPos[i]),(curr.x + xPos[i])) && map[curr.y + yPos[i]][curr.x + xPos[i]] == Enm) {
				for (size_t i = 0; i < length; i++)
				{
					Position temp = enemies[i].Pos();
					if ((curr.y + yPos[i]) == (temp.y / blockSize) && (curr.x + xPos[i]) == (temp.x / blockSize))
					{
						enemies[i].setNextPos(Position((curr.y + yPos[i]), (curr.x + xPos[i])));
					}
				}
			}
			if (inRangePLR((curr.y + yPos[i]), (curr.x + xPos[i])) && (map[curr.y + yPos[i]][curr.x + xPos[i]] == Passage) && !visited[curr.y + yPos[i]][curr.x + xPos[i]]) {
				q.push(Position((curr.y + yPos[i]), (curr.x + xPos[i])));
				visited[curr.y + yPos[i]][curr.x + xPos[i]] = true;
			}
		}

	}

}

bool Player::inRangePLR(int x, int y)
{
	return (x > 0 + blockSize && x < (hight / blockSize) && y > 0 + blockSize && y < (width / blockSize));
}
