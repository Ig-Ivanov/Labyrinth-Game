#ifndef __OBJECTIVES__
#define __OBJECTIVES__
#include "HelpFunc.h"

class Objectives
{
public:
	Objectives(Position _pos, SDL_Texture* _txt ,char _rep = Obj);
	~Objectives();

	void drawObjective(SDL_Renderer* renderer);
	void changeObjectiveRep(std::vector<std::string> & map);
	Position ObjCenter() { return Position(rect.x + (blockSize / 2), rect.y + (blockSize / 2)); }
	void drawObjBG(SDL_Renderer* renderer, SDL_Texture* txt);
	void updateObj(std::vector<std::string> & map);

private:
	char rep;
	Position pos;
	SDL_Rect rect;
	SDL_Texture* txt;
};

#endif // !__OBJECTIVES__

