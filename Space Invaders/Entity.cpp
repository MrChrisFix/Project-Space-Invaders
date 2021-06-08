#include "Entity.h"

void Entity::initSprite(float posX, float posY, float sprite_scale)
{
	this->sprite.setTexture(*this->texture);

	this->sprite.setScale(sprite_scale, sprite_scale);
	this->sprite.setPosition(posX, posY);
}

Entity::Entity(sf::Texture* texture_, float posX, float posY, float sprite_scale)
{
	this->texture = texture_;

	this->initSprite(posX, posY, sprite_scale);
}

Entity::~Entity()
{
	this->texture = nullptr;
}

void Entity::render(sf::RenderTarget& target)
{
  	target.draw(this->sprite);
}

sf::FloatRect Entity::getGBounds()
{
	return this->sprite.getGlobalBounds();
}
