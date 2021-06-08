#pragma once
#include "Entity.h"
#include "Timer.h"

class Gracz : public Entity
{
	const short int MOVEMENT_SPEED = 5;

	Timer cooldown;

	//Elementy rozgrywki
	short int zycia;

public:
	Gracz(sf::Texture* texture_, float posX, float posY);
	Gracz(sf::Texture* texture_, float posX, float posY, short int zycia_);
	~Gracz();

	void update();

	void move(float dirX);

	bool canAttack();

	//Elementy rozgrywki

	short int getZycia();

	void stracZycie();

	void restartStats();

	void setNew(float posX, float posY, short int zycia_);

};

