#include "Object.h"

Object::Object(Position _pos, SDL_Texture * _txt, char ch ,int _lives)
	:pos(_pos)
	,txt(_txt)
	,lives(_lives)
	,rep(ch)
{
	rect.x = _pos.x;
	rect.y = _pos.y;
	SDL_QueryTexture(txt, NULL, NULL, &rect.w, &rect.h);

}

Object::~Object()
{
}

void Object::draw(SDL_Renderer * renderer)
{
	SDL_RenderCopy(renderer,txt, 0, &rect);
}

void Object::changePos(Position pos)
{
	if (((rect.x + pos.x) >= 0 + blockSize) && ((rect.y + pos.y) >= 0 + blockSize) && ((rect.x + pos.x) < width - blockSize) && ((rect.y + pos.y) < hight - blockSize)) {
		bool movingX = false;
		bool movingY = false;
		if ((pos.x + rect.x) != rect.x) movingX = true;
		if ((pos.y + rect.y) != rect.y) movingY = true;

		bool inBetweenX = false;
		bool inBetweenY = false;
		if ((rect.x % blockSize) != 0)inBetweenX = true;
		if ((rect.y % blockSize) != 0)inBetweenY = true;

		if (inBetweenX && movingY)
		{
			if ((Center().x % blockSize) < blockSize / 2) {
				rect.x += 5;
			}
			else
			{
				rect.x -= 5;
			}
		}

		else if (inBetweenY && movingX) {
			if ((Center().y % blockSize) < blockSize / 2) {
				rect.y += 5;
			}
			else
			{
				rect.y -= 5;
			}
		}
		else
		{
			rect.x += pos.x;
			rect.y += pos.y;
		}
	}
}

void Object::drawBG(SDL_Renderer * renderer, SDL_Texture * txt)
{
	SDL_RenderCopy(renderer,txt, 0, &rect);
}

void Object::dies()
{
}