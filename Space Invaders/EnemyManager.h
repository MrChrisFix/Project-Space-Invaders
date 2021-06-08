#pragma once
#include "Enemy.h"
#include "Bullet.h"

class EnemyManager
{
	bool wLewo;

	std::vector<std::shared_ptr<Enemy>> enemies;

	//Czasomierze
	Timer enemyAttackCooldown;
	Timer ruch; ///< Jak czesto moga sie przeciwnicy ruszyc

	void initEnemies(std::map<std::string, sf::Texture*>& textures);

	void initTimers();

	//Ruch przeciwnikow
	void porusz();
	bool mozeDol(sf::Vector2f pos, bool lewo);

public:

	EnemyManager();
	~EnemyManager();

	void updateEnemies(std::vector<std::shared_ptr<Bullet>>& pociski, sf::Texture* enemy_bullet_texture, int& punkty);

	bool allDestroyed();

	void restart(std::map<std::string, sf::Texture*>& textures);

	void update();

	void render(sf::RenderTarget& target);


	std::vector<std::shared_ptr<Enemy>>* getEnemies();

	bool* getLewo();
};

