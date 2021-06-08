#include "Bullet.h"

Bullet::Bullet(sf::Texture* texture_, bool player_bullet_, float posX, float posY) : Entity(texture_, posX, posY, 2.f)
{
	if (player_bullet_)
	{
		this->MOVEMENT_SPEED = -10;
	}
	else
	{
		this->MOVEMENT_SPEED = 5;
	}
	this->player_bullet = player_bullet_;
}

Bullet::~Bullet()
{
}

void Bullet::update()
{
}

void Bullet::move()
{
	this->sprite.move(0.f, this->MOVEMENT_SPEED * 1.f);
}

bool Bullet::isPlayerBullet()
{
	return this->player_bullet;
}

