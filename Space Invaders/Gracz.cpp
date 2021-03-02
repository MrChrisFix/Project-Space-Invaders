#include "Gracz.h"


void Gracz::initSprite()
{
	this->sprite.setTexture(*this->texture);
	this->sprite.setScale(0.1f, 0.1f);
	this->sprite.setPosition(640.f, 600.f);
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

}

void Gracz::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
