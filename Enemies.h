#ifndef __ENEMIES__
#define __ENEMIES__
#include <iostream>
#include "Object.h"


class Enemy: public Object
{
public:
	Enemy(Position _pos, SDL_Texture* _txt, int _lives = 1, bool _canDig = false) : Object(_pos,_txt,Enm,_lives), canDig(canDig), path(nullptr){}
	virtual ~Enemy();

	Path* BFS(std::vector<std::string> & map);
	bool inRange(int x, int y);
	void getPath(std::vector<std::string> & map);
	virtual Position changeRep(std::vector<std::string> & map) override;
	void fillMatrix(bool** fill);
	Position getMove() { return move; }
	void updateEnemy(std::vector<std::string>& map);
	void setNextPos(Position _pos) { move = _pos; }

private:
	bool canDig;
	Path* path;
	Position move;
};
#endif // !__ENEMIES__

