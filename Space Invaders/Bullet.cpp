#include "Bullet.h"

void Bullet::initSprite(float posX, float posY)
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(2.5f, 2.5f);
	this->sprite.setPosition(posX-this->sprite.getGlobalBounds().width/2, posY);
}

Bullet::Bullet(sf::Texture* texture_, bool player_bullet, float posX, float posY)
{
	float posY2;
	if (player_bullet)
	{
		this->MOVEMENT_SPEED = -10;
		posY2 = posY - texture_->getSize().x * 2.5f;
	}
	else
	{
		this->MOVEMENT_SPEED = 5;
		posY2 = posY - texture_->getSize().x * 2.5f;
	}

	this->texture = texture_;

	this->initSprite(posX, posY2);
}

Bullet::~Bullet()
{
	this->texture = nullptr;
}

void Bullet::update()
{
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Bullet::move()
{
	this->sprite.move(0.f, this->MOVEMENT_SPEED * 1.f);
}

sf::FloatRect Bullet::getGBounds()
{
	return this->sprite.getGlobalBounds();
}

