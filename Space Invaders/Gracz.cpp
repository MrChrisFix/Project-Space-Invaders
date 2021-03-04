#include "Gracz.h"


void Gracz::initSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(2.5f, 2.5f);
	this->sprite.setPosition(640.f, 600.f);
}

void Gracz::updateCooldown()
{
	if (1.1*this->ATTACK_COOLDOWN > this->CURRENT_COOLDOWN)
	{
		this->CURRENT_COOLDOWN++;
	}
}

Gracz::Gracz(sf::Texture* texture_)
{
	this->texture = texture_;
	this->initSprite();
}

Gracz::~Gracz()
{
	this->texture = nullptr;
}

void Gracz::update()
{
	this->updateCooldown();
}

void Gracz::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

void Gracz::move(float dirX)
{
	if ((dirX <0 && this->sprite.getPosition().x > 100) || (dirX>0 && this->sprite.getPosition().x<1100))
		this->sprite.move(dirX * MOVEMENT_SPEED, 0.f);
}

sf::FloatRect Gracz::getGBounds()
{
	return this->sprite.getGlobalBounds();
}

bool Gracz::canAttack()
{
	if (this->ATTACK_COOLDOWN <= this->CURRENT_COOLDOWN)
	{
		this->CURRENT_COOLDOWN = 0;
		return true;
	}

	return false;
}
