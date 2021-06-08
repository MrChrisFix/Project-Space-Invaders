#pragma once
#include "Biblioteki.h"

class Entity
{
protected:
	sf::Texture* texture;
	sf::Sprite sprite;

	//Prywatne funkcje
	void initSprite(float posX, float posY, float sprite_scale);

public:
	Entity(sf::Texture* texture_, float posX, float posY, float sprite_scale);
	virtual ~Entity();


	void render(sf::RenderTarget& target);

	virtual void update() = 0;

	sf::FloatRect getGBounds();

};

