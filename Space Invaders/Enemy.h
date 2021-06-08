#pragma once
#include "Entity.h"
#include "Timer.h"

class Enemy : public Entity
{
	float ODDALENIE;
	const float MOVEMENT_SPEED = 10.f;

	sf::Vector2f Pozycja_poczatkowa;

	sf::Texture* textura2;

	unsigned short int punkty;
	
public:

	Enemy(sf::Texture* texture_, sf::Texture* texture2, float posX, float posY, unsigned short int pkt);
	Enemy(sf::Texture* texture_, sf::Texture* texture2, float posX, float posY, unsigned short int pkt, short int oddalenie);
	~Enemy();

	void update();

	void move(char STAN_RUCHU);

	unsigned short int ilePunktow();

	sf::Vector2f shoot_pos();

	sf::Vector2f Position();

	float getOddalenie();
};

