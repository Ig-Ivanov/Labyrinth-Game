#ifndef __OBJECT__
#define __OBJECT__
#include <iostream>
#include "HelpFunc.h"

class Object
{
public:
	Object(Position _pos, SDL_Texture* _txt, char ch ,int _lives = 0);
	/*Object(Object& other) = delete;
	Object& operator=(Object& other) = delete;*/
	virtual ~Object();

	virtual void draw(SDL_Renderer* renderer);
	virtual void changePos(Position pos);
	Position Center() { return Position(rect.x + (blockSize / 2), rect.y + (blockSize / 2)); }
	Position Pos(){ return Position(rect.x, rect.y); }
	void drawBG(SDL_Renderer* renderer , SDL_Texture* txt);
	virtual Position changeRep(std::vector<std::string> & map) = 0;
	virtual void dies();
	int decreseLive() { return lives -= 1; }
	int getLive() { return lives; }

protected:
	char rep;
	Position pos;
	int lives;
	SDL_Texture* txt;
	SDL_Rect rect;
};

#endif // !__OBJECT__
