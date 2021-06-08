#include "Gracz.h"

Gracz::Gracz(sf::Texture* texture_, float posX, float posY) : Entity(texture_, posX, posY, 2.f), cooldown(50)
{
	this->zycia = 3;
}

Gracz::Gracz(sf::Texture* texture_, float posX, float posY, short int zycia_) : Entity(texture_, posX, posY, 2.f), cooldown(50)
{
	this->zycia = zycia_;
}

Gracz::~Gracz()
{
}

void Gracz::update()
{
	this->cooldown.update();
}

void Gracz::move(float dirX)
{
	if ((dirX <0 && this->sprite.getPosition().x > 100) || (dirX>0 && this->sprite.getPosition().x<1100))
		this->sprite.move(dirX * MOVEMENT_SPEED, 0.f);
}

bool Gracz::canAttack()
{
	return this->cooldown.avaliable();
}

short int Gracz::getZycia()
{
	return this->zycia;
}

void Gracz::stracZycie()
{
	this->zycia--;
}

void Gracz::restartStats()
{
	this->zycia = 3;
	this->sprite.setPosition(640.f - this->sprite.getGlobalBounds().width / 2, 600.f);
}

void Gracz::setNew(float posX, float posY, short int zycia_)
{
	this->sprite.setPosition(posX, posY);
	this->zycia = zycia_;
}
