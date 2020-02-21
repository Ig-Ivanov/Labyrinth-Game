#include "Objectives.h"

Objectives::Objectives(Position _pos, SDL_Texture * _txt, char _rep)
	:pos(_pos)
	,txt(_txt)
	,rep(_rep)
{
	rect.x = _pos.x;
	rect.y = _pos.y;
	SDL_QueryTexture(txt, NULL, NULL, &rect.w, &rect.h);
}

Objectives::~Objectives()
{
}

void Objectives::drawObjective(SDL_Renderer * renderer)
{

	SDL_RenderCopy(renderer, txt, 0, &rect);
}

void Objectives::changeObjectiveRep(std::vector<std::string>& map)
{
	Position curr((rect.x / blockSize), (rect.y / blockSize));
	if (map[curr.y][curr.x] != rep)
	{
		map[curr.y][curr.x] = rep;
	}
}

void Objectives::drawObjBG(SDL_Renderer * renderer, SDL_Texture * txt)
{
	SDL_RenderCopy(renderer, txt, 0, &rect);
}

void Objectives::updateObj(std::vector<std::string>& map)
{
	Position curr((rect.x / blockSize), (rect.y / blockSize));
	map[curr.y][curr.x] = Passage;
}
