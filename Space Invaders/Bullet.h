#pragma once
#include "Entity.h"

class Bullet : public Entity
{
	short int MOVEMENT_SPEED;

	bool player_bullet;

public:

	Bullet(sf::Texture* texture_, bool player_bullet_, float posX, float posY);
	~Bullet();

	void update() override;

	void move();

	bool isPlayerBullet();

};

