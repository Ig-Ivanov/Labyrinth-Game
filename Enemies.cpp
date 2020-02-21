#include "Enemies.h"

Enemy::~Enemy()
{
}

Path* Enemy::BFS(std::vector<std::string> & map)
{
	Position temp;
	temp.x = rect.x / blockSize;
	temp.y = rect.y / blockSize;

	bool** visited = new bool*[hight / blockSize];
	for (size_t i = 0; i < hight / blockSize; i++)
	{
		visited[i] = new bool[width / blockSize];
	}
	fillMatrix(visited);
	std::queue<Path*> q;
	Path* curr = new Path(temp);
	q.push(curr);

	while (!q.empty())
	{
		Path* p = q.front();
		q.pop();
		if (map[p->pos.y][p->pos.x] == Plr)
		{
			for (size_t i = 0; i < hight / blockSize; i++)
			{
				delete visited[i];
				//	visited[i] = { false, };
			}
			delete[] visited;
			return p;
		}
		temp = p->pos;
		temp.x -= 1;
		if(inRange(temp.y,temp.x) && (!visited[temp.y][temp.x]) && map[temp.y][temp.x] != Wall){
			visited[temp.y][temp.x] = true;
			Path* curr = new Path(temp, p);
			q.push(curr);
		}

		temp = p->pos;
		temp.x += 1;
		if (inRange(temp.y, temp.x) && (!visited[temp.y][temp.x]) && map[temp.y][temp.x] != Wall) {
			visited[temp.y][temp.x] = true;
			Path* curr = new Path(temp, p);
			q.push(curr);
		}

		temp = p->pos;
		temp.y -= 1;
		if (inRange(temp.y, temp.x) && (!visited[temp.y][temp.x]) && map[temp.y][temp.x] != Wall) {
			visited[temp.y][temp.x] = true;
			Path* curr = new Path(temp, p);
			q.push(curr);
		}

		temp = p->pos;
		temp.y += 1;
		if (inRange(temp.y, temp.x) && (!visited[temp.y][temp.x]) && map[temp.y][temp.x] != Wall) {
			visited[temp.y][temp.x] = true;
			Path* curr = new Path(temp, p);
			q.push(curr);
		}
	}
	for (size_t i = 0; i < hight / blockSize; i++)
	{
		delete visited[i];
		//	visited[i] = { false, };
	}
	delete[] visited;
	return nullptr;
}

bool Enemy::inRange(int x, int y)
{
	return (x > 0 && x < (hight / blockSize) && y > 0 && y < (width / blockSize));
}

void Enemy::getPath(std::vector<std::string> & map)
	{
	path = BFS(map);
	if(path != nullptr && path->parent != nullptr)
	while (path->parent->parent != nullptr)
	{
		path = path->parent;
	}
	if((rect.x % blockSize == 0) && (rect.y % blockSize == 0) && path != nullptr) {
		move.x = (path->pos.x - (rect.x / blockSize)) * 5;
		move.y = (path->pos.y - (rect.y / blockSize)) * 5;
	}
}

Position Enemy::changeRep(std::vector<std::string>& map)
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
	return Position(-1,-1);
}

void Enemy::fillMatrix(bool ** fill)
{
	for (size_t i = 0; i < hight / blockSize; i++)
	{
		for (size_t j = 0; j < width / blockSize; j++)
		{
			fill[i][j] = false;
		}
	}
}

void Enemy::updateEnemy(std::vector<std::string>& map)
{
	Position curr((rect.x / blockSize), (rect.y / blockSize));
	map[curr.y][curr.x] = Passage;
}
