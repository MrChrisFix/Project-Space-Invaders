#pragma once

#include "Biblioteki.h"

class Gracz
{
protected:
	sf::Texture* texture;
	sf::Sprite sprite;
	const short int MOVEMENT_SPEED = 10;
	const short int ATTACK_COOLDOWN = 50;
	short int CURRENT_COOLDOWN;

	//Prywatne funkcje
	void initSprite();
	void updateCooldown();

public:
	Gracz(sf::Texture* texture_);
	~Gracz();

	void update();
	void render(sf::RenderTarget &target);

	void move(float dirX);

	sf::FloatRect getGBounds();

	bool canAttack();


};

