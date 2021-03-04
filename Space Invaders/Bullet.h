#pragma once
#include "Biblioteki.h"

class Bullet
{
	sf::Texture* texture;
	sf::Sprite sprite;
	short int MOVEMENT_SPEED;

	//Prywatne funckje
	void initSprite(float posX, float posY);


public:

	Bullet(sf::Texture* texture_, bool player_bullet, float posX, float posY);
	~Bullet();

	void update();
	void render(sf::RenderTarget& target);

	void move();

	sf::FloatRect getGBounds();

};

