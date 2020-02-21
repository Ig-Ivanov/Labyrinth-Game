#ifndef __PLAYER__
#define __PLAYER__
#include <iostream>
#include "Enemies.h"

const SDL_Scancode UP = SDL_SCANCODE_UP;
const SDL_Scancode DOWN = SDL_SCANCODE_DOWN;
const SDL_Scancode LEFT = SDL_SCANCODE_LEFT;
const SDL_Scancode RIGHT = SDL_SCANCODE_RIGHT;
const SDL_Scancode SHOOT = SDL_SCANCODE_SPACE;


class Player: public Object
{
public:
	Player(Position _pos, SDL_Texture* _txt, int _lives = 1) : Object(_pos,_txt,Plr,_lives),score(0) {}
	virtual ~Player();

	virtual Position changeRep(std::vector<std::string> & map) override;
	void updateScore(int _score) { score += _score; }
	int loseLive() { return Object::decreseLive(); }
	void BFSPLR(std::vector<std::string>& map, std::vector<Enemy>& enemies);
	bool inRangePLR(int x, int y);

private:
	int score;

};
#endif // !__PLAYER__

