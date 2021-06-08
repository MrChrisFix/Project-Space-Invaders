#pragma once
#include "Biblioteki.h"
#include "MenuType.h"
#include "Bullet.h"
#include "Gracz.h"
#include "Enemy.h"
#include <vector>

class Odczyt_Zapis : public MenuType
{
	int wybranyNumer;

	void initButtons() override;

	bool czyIstnieje(int numer);

	void loadOpisy(); //Przysz³oœæ

	void saveOpisy(); //Przysz³oœæ

public:
	Odczyt_Zapis(sf::Font* font, sf::RenderWindow* target);
	~Odczyt_Zapis();

	/////CZESC ZAPISOWA
	//Zapis odczyt
	void zapisz(std::vector<std::shared_ptr<Enemy>> przeciwnicy, std::vector<std::shared_ptr<Bullet>> pociski, Gracz* player, bool lewo, int punkty);

	void odczytaj(std::map<std::string, sf::Texture*> tekstury,
		std::vector<std::shared_ptr<Enemy>>* przeciwnicy, std::vector<std::shared_ptr<Bullet>>& pociski, Gracz* player, bool& lewo, int& punkty);

	/////CZESC WIZUALNA

	int detectButtonClick(bool& pressed, bool czyZapis);
	int detectButtonClick(bool& pressed) override;

	void update() override;

	void render() override;

};
