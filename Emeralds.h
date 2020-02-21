#ifndef __EMERALDS__
#define __EMERALDS__
#include "Objectives.h"

class Emeralds: public Objectives
{
public:
	Emeralds(Position _pos, SDL_Texture* _txt, int _score = 300):Objectives(_pos,_txt), score(_score){}
	~Emeralds();

	int getScore() { return score; }
	

private:
	int score;
};

#endif // !__EMERALDS__

