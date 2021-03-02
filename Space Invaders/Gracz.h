#pragma once

#include "Biblioteki.h"

class Gracz
{
protected:
	sf::Texture* texture;
	sf::Sprite sprite;

	void initSprite();

public:
	Gracz(sf::Texture* texture_);
	~Gracz();

	void update();

	void render(sf::RenderTarget &target);


};

