#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture_, sf::Texture* texture2, float posX, float posY, unsigned short int pkt) : Entity(texture_, posX, posY, 4.f)
{
	this->ODDALENIE = 100;
	this->textura2 = texture2;
	this->punkty = pkt;
	this->Pozycja_poczatkowa = { posX, posY };
}

Enemy::Enemy(sf::Texture* texture_, sf::Texture* texture2, float posX, float posY, unsigned short int pkt, short int oddalenie) : Entity(texture_, posX, posY, 4.f)
{
	this->ODDALENIE = oddalenie;
	this->textura2 = texture2;
	this->punkty = pkt;
	this->Pozycja_poczatkowa = { posX, posY };
}

Enemy::~Enemy()
{
	this->texture = nullptr;
}

void Enemy::update()
{

}

void Enemy::move(char STAN_RUCHU)
{
	
	float przesuniecie = this->MOVEMENT_SPEED * 0.5f;
	switch (STAN_RUCHU)
	{
	case 'l': //left
	{
		this->sprite.move(-przesuniecie, 0.f);
		this->ODDALENIE += przesuniecie;
		if (this->ODDALENIE >= 200)
		{
			this->ODDALENIE = 0;
		}
		break;
	}
	case 'd': //down
	{
		this->sprite.move(0.f, przesuniecie);
		this->ODDALENIE += przesuniecie;
		if (this->ODDALENIE >= 10)
		{
			this->ODDALENIE = 0;
			break;
		}
		break;
	}
	case 'r': //right
	{
		this->sprite.move(przesuniecie, 0.f);
		this->ODDALENIE += przesuniecie;
		if (this->ODDALENIE >= 200)
		{
			this->ODDALENIE = 0;
		}
		break;
	}
	default:
		break;
	}

	if (this->sprite.getTexture() == this->texture)
		this->sprite.setTexture(*this->textura2);
	else
		this->sprite.setTexture(*this->texture);
}

unsigned short int Enemy::ilePunktow()
{
	return this->punkty;
}

sf::Vector2f Enemy::shoot_pos()
{
	return sf::Vector2f(this->sprite.getGlobalBounds().left + this->sprite.getGlobalBounds().width / 2,
		this->sprite.getGlobalBounds().top + this->sprite.getGlobalBounds().height
	);
}

sf::Vector2f Enemy::Position()
{
	return this->sprite.getPosition();
}

float Enemy::getOddalenie()
{
	return this->ODDALENIE;
}
