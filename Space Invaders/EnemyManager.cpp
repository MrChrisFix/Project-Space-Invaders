#include "EnemyManager.h"



void EnemyManager::initEnemies(std::map<std::string, sf::Texture*>& textures)
{
	sf::Texture* temp1;
	sf::Texture* temp2;
	for (int j = 0; j < 5; j++)
	{
		if (j == 0) { temp1 = textures["GREEN_ALIEN1"]; temp2 = textures["GREEN_ALIEN2"]; }
		else if (j == 1 || j == 2) { temp1 = textures["BLUE_ALIEN1"]; temp2 = textures["BLUE_ALIEN2"]; }
		else { temp1 = textures["RED_ALIEN1"]; temp2 = textures["RED_ALIEN2"]; }
		for (int i = 0; i < 15; i++)
		{
			enemies.push_back(std::make_shared<Enemy>(temp1, temp2, 200.f + 60 * i, 80.f + 50.f * j, 5 - j)); //TODO: Polepszyc pozycje
		}
	}
	temp1 = temp2 = nullptr;
}

void EnemyManager::initTimers()
{
	this->enemyAttackCooldown.reset();
}

EnemyManager::EnemyManager() : enemyAttackCooldown(100), ruch(50)
{
	this->initTimers();
	this->wLewo = false;
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::updateEnemies(std::vector<std::shared_ptr<Bullet>>& pociski, sf::Texture* enemy_bullet_texture, int& punkty)
{
	//Zabijanie przeciwnikow
	unsigned short int licznik_i = 0;
	for (auto& i : pociski)
	{
		unsigned short int licznik_j = 0;
		for (auto& j : this->enemies)
		{
			if (i != nullptr && j != nullptr)
			{
				if (i->getGBounds().intersects(j->getGBounds()) && i->isPlayerBullet())
				{
					pociski.erase(pociski.begin() + licznik_i);
					licznik_i--;
					punkty += this->enemies[licznik_j]->ilePunktow();
					this->enemies.erase(this->enemies.begin() + licznik_j);
					licznik_j--;
				}
			}
			licznik_j++;
		}
		licznik_i++;
	}

	//Ruch przeciwnikow
	this->ruch.update();
	this->porusz();

	this->enemyAttackCooldown.update();


	//Wybieranie losowego przeciwnika do strzalu
	if (enemies.size() != 0 && this->enemyAttackCooldown.avaliable())
	{
		int x = rand() % (this->enemies.size());
		sf::Vector2f Pos = this->enemies[x]->shoot_pos();
		pociski.push_back(std::make_shared<Bullet>(
			enemy_bullet_texture, /*TODO: zmienic na inna teksture*/
			false, Pos.x, Pos.y)
		);
	}
}

bool EnemyManager::allDestroyed()
{
	//Wszyscy przeciwnicy zostali pokonani
	if (this->enemies.empty())
	{
		//TODO: To jest tymczasowe, nalezy wczytac nowa fale przciwnikow
		return true;
	}

	return false;
}

void EnemyManager::restart(std::map<std::string, sf::Texture*>& textures)
{
	this->enemies.clear();

	this->initEnemies(textures);
}

void EnemyManager::porusz()
{
	if (this->ruch.avaliable())
	{
		bool canGoDown = false;
		for (auto& i : this->enemies)
		{
			if (canGoDown) break;
			canGoDown = mozeDol(i->Position(), this->wLewo);
		}
		if (canGoDown)
		{
			for (auto& i : this->enemies)
				i->move('d');
			this->wLewo = !this->wLewo;
		}
		else
		{
			for (auto& i : this->enemies)
			{
				if (this->wLewo) i->move('l');
				else i->move('r');
			}
		}
	}

}

bool EnemyManager::mozeDol(sf::Vector2f pos, bool lewo)
{
	if (( pos.x > 1050 && !lewo) || (lewo && pos.x < 150))
	{
		return true;
	}

	return false;
}

void EnemyManager::update()
{

}

void EnemyManager::render(sf::RenderTarget& target)
{
	for (auto& i : this->enemies)
		i->render(target);
}

std::vector<std::shared_ptr<Enemy>>* EnemyManager::getEnemies()
{
	return &this->enemies;
}

bool* EnemyManager::getLewo()
{
	return &this->wLewo;
}
