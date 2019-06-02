// SAPER

#include "pch.h"
#include <iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<sstream>
bool CzyBylaWylosowana(int wyl, int tab[], int n)
{
	if (n <= 0)
		return false;
	int i = 0;
	do
	{
		if (tab[i] == wyl)
			return true;
		i++;
	} while (i < n);

	return false;
}
using namespace sf;
using namespace std;
class Pole
{
public:
	int nr_pola;
	string rodzaj_pola;
	virtual void Dodaj(int n, string r) = 0;
};
class Mina : public Pole
{
public:
	Sprite Mina_sprite;
	Texture Mina_tekstura;
	void Dodaj(int n, string r)
	{
		nr_pola = n;
		rodzaj_pola = r;
	}
};
class Nieodkyte_Pole : public Pole
{
public:
	int ile_razy_klikniete;
	int ile_sasiadów_min;
	int zajete;
	int disabled;
	int puste;
	int odkryte;
	int odkryte2;
	string co_tam_jest;
	Sprite Nieodkryte_Pole_sprite;
	Texture Nieodkryte_Pole_tekstura;
	void Dodaj(int n, string r)
	{
		nr_pola = n;
		rodzaj_pola = r;
	}
};
int main()
{
	srand(time(NULL));
	bool t = true;
	int koniec = 0;
	int wylosowana, j, xx = 0, i = 0, wylosowanych = 0;
	int ogr2 = 0, ogr3 = 0, ogr4 = 0, ogr5 = 0, ogr6 = 0, ogr7 = 0, ogr8 = 0;
	int ogran = 0;
	int liczba;
	RenderWindow window{ VideoMode{1280,720},"Saper" };
	Font TimesNewRoman;
	TimesNewRoman.loadFromFile("Obrazy/czcionka.ttf");
	string s = "YOU LOST";
	string sp = "WIN";
	string licznik = "99";
	stringstream pom;
	Text txt(s, TimesNewRoman);
	txt.setCharacterSize(30);
	txt.setFillColor(Color::Red);
	txt.setPosition(10, 10);
	Text Licznik(licznik, TimesNewRoman);
	Licznik.setCharacterSize(50);
	Licznik.setFillColor(Color::Red);
	Licznik.setPosition(1200, 10);
	Text txt1(sp, TimesNewRoman);
	txt1.setCharacterSize(30);
	txt1.setFillColor(Color::Green);
	txt1.setPosition(10, 10);
	Event event;
	//LOSOWANIE POZYCJI MIN
	int Pozycje_min[99];
	do
	{
		wylosowana = rand() % 540;
		if (CzyBylaWylosowana(wylosowana, Pozycje_min, wylosowanych) == false)
		{
			Pozycje_min[wylosowanych] = wylosowana;
			wylosowanych++;
		}
	} while (wylosowanych < 99);
	Texture mine, nieodkryty_kwadrat, flaga, jedynka, dwojka, trojka, czworka, piatka;
	nieodkryty_kwadrat.loadFromFile("Obrazy/nieodkryte.jpg");
	mine.loadFromFile("Obrazy/mina.jpg");
	flaga.loadFromFile("Obrazy/flaga.png");
	jedynka.loadFromFile("Obrazy/jeden.jpg");
	dwojka.loadFromFile("Obrazy/dwa.jpg");
	trojka.loadFromFile("Obrazy/trzy.png");
	czworka.loadFromFile("Obrazy/cztery.png");
	piatka.loadFromFile("Obrazy/pięć.png");
	// UMIESZCZANIE MIN
	Mina classMines[99];
	for (int i = 0; i < 99; i++)
	{
		classMines[i].Dodaj(Pozycje_min[i], "Mina");
		classMines[i].Mina_sprite = Sprite(mine);
		classMines[i].Mina_tekstura = mine;
		classMines[i].Mina_sprite.setPosition(100 + 35 * (Pozycje_min[i] % 30), 10 + 35 * (Pozycje_min[i] / 30 + 1));
	}
	//  TWORZENIE PLANSZY 
	Nieodkyte_Pole classNieodkryte[540];
	int ogrx = 0, ogry = 35, ogr = 1;
	for (int i = 0; i < 540; i++)
	{
		classNieodkryte[i].Dodaj(i, "Nieodkryte");
		classNieodkryte[i].ile_razy_klikniete = 0;
		classNieodkryte[i].ile_sasiadów_min = 0;
		classNieodkryte[i].disabled = 0;
		classNieodkryte[i].Nieodkryte_Pole_sprite = Sprite(nieodkryty_kwadrat);
		classNieodkryte[i].Nieodkryte_Pole_tekstura = nieodkryty_kwadrat;
		classNieodkryte[i].Nieodkryte_Pole_sprite.setColor(Color(0, 150, 200, 255));
		classNieodkryte[i].odkryte2 = 0;
		if (i < ogrx + 30)
		{
			classNieodkryte[i].Nieodkryte_Pole_sprite.setPosition(100 + 35 * (i - ogrx), 10 + ogry * ogr);
		}
		if (i % 30 == 0 and i != 0)
		{
			ogrx += 30;
			ogr += 1;
			classNieodkryte[i].Nieodkryte_Pole_sprite.setPosition(100 + 35 * (i - ogrx), 10 + ogry * ogr);
		}
	}
	// USTAWIANIE LICZB NA ODPOWIEDNICH MIEJSCACH
	for (int i = 0; i < 540; i++)
	{
		t = true;
		j = 0;
		while (j < 99)
		{
			if (classNieodkryte[i].nr_pola == classMines[j].nr_pola)
			{
				classNieodkryte[i].ile_sasiadów_min = -1;
				t = false;
				break;
			}
			j++;
		}
		if (t and i == 0)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i + 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i + 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i + 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				j++;
			}
		}
		else if (t and i == 510)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i + 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i - 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i - 29].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				j++;
			}
		}
		else if (t and i == 29)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i - 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i + 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i + 29].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;

				}
				j++;
			}
		}
		else if (t and i == 539)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i - 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i - 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i - 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				j++;
			}
		}
		else if (t and i > 0 and i < 29)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0; ogr2 = 0; ogr3 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i + 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i + 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i + 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				if (classNieodkryte[i + 29].nr_pola == classMines[j].nr_pola and ogr2 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr2 += 1;
				}
				if (classNieodkryte[i - 1].nr_pola == classMines[j].nr_pola and ogr3 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr3 += 1;
				}
				j++;
			}
		}
		else if (t and i > 510 and i < 539)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0; ogr2 = 0; ogr3 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i + 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i - 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i - 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				if (classNieodkryte[i - 29].nr_pola == classMines[j].nr_pola and ogr2 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr2 += 1;
				}
				if (classNieodkryte[i - 1].nr_pola == classMines[j].nr_pola and ogr3 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr3 += 1;
				}
				j++;
			}
		}
		else if (t and i % 30 == 0 and i != 0 and i != 510)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0; ogr2 = 0; ogr3 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i + 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i + 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i + 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				if (classNieodkryte[i - 29].nr_pola == classMines[j].nr_pola and ogr2 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr2 += 1;
				}
				if (classNieodkryte[i - 30].nr_pola == classMines[j].nr_pola and ogr3 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr3 += 1;
				}
				j++;
			}
		}
		else if (t and i % 30 == 29 and i != 29 and i != 539)
		{
			j = 0; ogran = 0; ogr6 = 0; ogr7 = 0; ogr2 = 0; ogr3 = 0;
			while (j < 99)
			{
				if (classNieodkryte[i - 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i + 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i - 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				if (classNieodkryte[i + 29].nr_pola == classMines[j].nr_pola and ogr2 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr2 += 1;
				}
				if (classNieodkryte[i - 30].nr_pola == classMines[j].nr_pola and ogr3 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr3 += 1;
				}
				j++;
			}
		}
		else if (t and i != 0 and i != 510 and i != 29 and i != 539 and i % 30 != 0 and i % 30 != 29 and i > 30 and i < 510)
		{
			j = 0;
			ogr2 = 0; ogr3 = 0; ogr4 = 0; ogr5 = 0; ogr6 = 0; ogr7 = 0; ogr8 = 0; ogran = 0;
			while (j < 99)
			{
				if (classNieodkryte[i + 1].nr_pola == classMines[j].nr_pola and ogran == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogran += 1;
				}
				if (classNieodkryte[i - 1].nr_pola == classMines[j].nr_pola and ogr2 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr2 += 1;
				}
				if (classNieodkryte[i - 30].nr_pola == classMines[j].nr_pola and ogr3 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr3 += 1;
				}
				if (classNieodkryte[i - 29].nr_pola == classMines[j].nr_pola and ogr4 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr4 += 1;
				}
				if (classNieodkryte[i - 31].nr_pola == classMines[j].nr_pola and ogr5 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr5 += 1;
				}
				if (classNieodkryte[i + 30].nr_pola == classMines[j].nr_pola and ogr6 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr6 += 1;
				}
				if (classNieodkryte[i + 31].nr_pola == classMines[j].nr_pola and ogr7 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr7 += 1;
				}
				if (classNieodkryte[i + 29].nr_pola == classMines[j].nr_pola and ogr8 == 0)
				{
					classNieodkryte[i].ile_sasiadów_min += 1;
					ogr8 += 1;
				}
				j++;
			}
		}
	}
	for (int i = 0; i < 540; i++)
	{
		if (classNieodkryte[i].ile_sasiadów_min == 0)
		{
			classNieodkryte[i].co_tam_jest = "puste";
		}
		else if (classNieodkryte[i].ile_sasiadów_min == 1)
		{
			classNieodkryte[i].co_tam_jest = "jedynka";
			classNieodkryte[i].Nieodkryte_Pole_tekstura = jedynka;
		}
		else if (classNieodkryte[i].ile_sasiadów_min == 2)
		{
			classNieodkryte[i].co_tam_jest = "dwojka";
			classNieodkryte[i].Nieodkryte_Pole_tekstura = dwojka;
		}
		else if (classNieodkryte[i].ile_sasiadów_min == 3)
		{
			classNieodkryte[i].co_tam_jest = "trojka";
			classNieodkryte[i].Nieodkryte_Pole_tekstura = trojka;
		}
		else if (classNieodkryte[i].ile_sasiadów_min == 4)
		{
			classNieodkryte[i].co_tam_jest = "czworka";
			classNieodkryte[i].Nieodkryte_Pole_tekstura = czworka;
		}
		else if (classNieodkryte[i].ile_sasiadów_min == 5)
		{
			classNieodkryte[i].co_tam_jest = "piatka";
			classNieodkryte[i].Nieodkryte_Pole_tekstura = piatka;
		}
		else if (classNieodkryte[i].ile_sasiadów_min == -1)
		{
			classNieodkryte[i].co_tam_jest = "mina";
			classNieodkryte[i].Nieodkryte_Pole_tekstura = mine;
		}
	}
	while (window.isOpen())
	{
		window.clear(Color::White);
		window.pollEvent(event);
		Text Licznik(licznik, TimesNewRoman);
		Licznik.setCharacterSize(50);
		Licznik.setFillColor(Color::Red);
		Licznik.setPosition(1200, 10);
		window.draw(Licznik);
		if (koniec == 1)
		{
			window.draw(txt);
		}
		for (int i = 0; i < 540; i++)
		{
			window.draw(classNieodkryte[i].Nieodkryte_Pole_sprite);
		}
		/*for (int i = 0; i <99 ; i++)
		{
			window.draw(classMines[i].Mina_sprite);
		}*/
		if (event.type == Event::Closed)
		{
			window.close();
			break;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Vector2i pos = Mouse::getPosition();
			int x = (pos.x - 429) / 35;
			int y = (pos.y - 261) / 35;
			if (x >= 0 and x <= 30 and y >= 0 and y <= 18)
			{
				if (classNieodkryte[x + 30 * y].ile_sasiadów_min > 0 and classNieodkryte[x + 30 * y].disabled == 0)
				{
					classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setColor(Color::White);
					classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[x + 30 * y].Nieodkryte_Pole_tekstura);
					classNieodkryte[x + 30 * y].zajete = 1;
					classNieodkryte[x + 30 * y].odkryte2 = 1;
				}
				else if (classNieodkryte[x + 30 * y].ile_sasiadów_min == 0 and classNieodkryte[x + 30 * y].disabled == 0)
				{
					classNieodkryte[x + 30 * y].zajete = 1;
					classNieodkryte[x + 30 * y].odkryte2 = 1;
					// PUSTE W PRAWO
					i = x;
					j = y;
					int ix = x;
					int jy = y;
					while ((i + 30 * j) < (30 + 30 * j) and classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
					{
						if (classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
						{
							classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * j].odkryte2 = 1;
						}
						i++;
						if (i == 30)
						{
							i--;
						}
						jy = y;
						while ((i + 30 * jy) > i and classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
							{
								classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[i + 30 * jy].odkryte2 = 1;
								if (classNieodkryte[i - 1 + 30 * jy].ile_sasiadów_min != 0 and i != 0)
								{
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i - 1 + 30 * jy].odkryte2 = 1;
								}
								if (classNieodkryte[i + 1 + 30 * jy].ile_sasiadów_min != 0 and i != 29)
								{
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i + 1 + 30 * jy].odkryte2 = 1;
								}
							}
							jy--;
						}
						if (classNieodkryte[i + 30 * jy].ile_sasiadów_min != 0)
						{
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * jy].Nieodkryte_Pole_tekstura);
							classNieodkryte[i + 30 * jy].odkryte2 = 1;
						}
						else
						{
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * jy].odkryte2 = 1;
						}
						jy = y;
						while ((i + 30 * jy) < (i + 30 * 17) and classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
							{
								classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[i + 30 * jy].odkryte2 = 1;
								if (classNieodkryte[i - 1 + 30 * jy].ile_sasiadów_min != 0 and i != 0)
								{
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i - 1 + 30 * jy].odkryte2 = 1;
								}
								if (classNieodkryte[i + 1 + 30 * jy].ile_sasiadów_min != 0 and i != 29)
								{
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i + 1 + 30 * jy].odkryte2 = 1;
								}
							}
							jy++;
						}
						i++;
					}
					if (i == 30)
						i--;
					if (classNieodkryte[i + 30 * jy].ile_sasiadów_min != 0)
					{
						classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
						classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * jy].Nieodkryte_Pole_tekstura);
						classNieodkryte[i + 30 * jy].odkryte2 = 1;
					}
					else
					{
						classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
						classNieodkryte[i + 30 * jy].odkryte2 = 1;
					}
					if (i == 30)
						i--;
					if ((i + 30 * j) != (29 + 30 * j))
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * j].Nieodkryte_Pole_tekstura);
						classNieodkryte[i + 30 * j].odkryte2 = 1;
					}
					// PUSTE W LEWO
					i = x;
					jy = y;
					j = y;
					while ((i + 30 * j) > (30 * j) and classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
					{
						if (classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
						{
							classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * j].odkryte2 = 1;
						}
						i--;
						jy = y;
						while ((i + 30 * jy) > i and classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
							{
								classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[i + 30 * jy].odkryte2 = 1;
								if (classNieodkryte[i - 1 + 30 * jy].ile_sasiadów_min != 0 and i != 0)
								{
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i - 1 + 30 * jy].odkryte2 = 1;
								}
								if (classNieodkryte[i + 1 + 30 * jy].ile_sasiadów_min != 0)
								{
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i + 1 + 30 * jy].odkryte2 = 1;
								}
							}
							jy--;
						}
						if (classNieodkryte[i + 30 * jy].ile_sasiadów_min != 0)
						{
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * jy].Nieodkryte_Pole_tekstura);
							classNieodkryte[i + 30 * jy].odkryte2 = 1;

						}
						else
						{
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * jy].odkryte2 = 1;
						}
						jy = y;
						while ((i + 30 * jy) < (i + 30 * 17) and classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[i + 30 * jy].ile_sasiadów_min == 0)
							{
								classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[i + 30 * jy].odkryte2 = 1;
								if (classNieodkryte[i - 1 + 30 * jy].ile_sasiadów_min != 0 and i != 0)
								{
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i - 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i - 1 + 30 * jy].odkryte2 = 1;
								}
								if (classNieodkryte[i + 1 + 30 * jy].ile_sasiadów_min != 0)
								{
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 1 + 30 * jy].Nieodkryte_Pole_tekstura);
									classNieodkryte[i + 1 + 30 * jy].odkryte2 = 1;
								}
							}
							jy++;
						}
						if (classNieodkryte[i + 30 * jy].ile_sasiadów_min != 0)
						{
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * jy].Nieodkryte_Pole_tekstura);
							classNieodkryte[i + 30 * jy].odkryte2 = 1;
						}
						else
						{
							classNieodkryte[i + 30 * jy].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * jy].odkryte2 = 1;
						}
					}
					if (classNieodkryte[i + 30 * j].ile_sasiadów_min != 0)
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * j].Nieodkryte_Pole_tekstura);
						classNieodkryte[i + 30 * j].odkryte2 = 1;
					}
					else
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
						classNieodkryte[i + 30 * jy].odkryte2 = 1;
					}
					// PUSTE W GÓRE
					ix = x;
					j = y;
					i = x;
					while ((i + 30 * j) > i and classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
					{
						if (classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
						{
							classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * j].odkryte2 = 1;
						}
						j--;
						ix = x;
						while ((ix + 30 * j) < (30 + 30 * j) and classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
							{
								classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[ix + 30 * j].odkryte2 = 1;
								if (classNieodkryte[ix + 30 * (j - 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_tekstura);
								}
								if (classNieodkryte[ix + 30 * (j + 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_tekstura);
								}
							}
							ix++;
						}
						if (ix == 30)
							ix--;
						if ((ix + 30 * j) != (29 + 30 * j))
						{
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * j].Nieodkryte_Pole_tekstura);
							classNieodkryte[ix + 30 * j].odkryte2 = 1;
						}
						ix = x;
						while ((ix + 30 * j) > (30 * j) and classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
							{
								classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[ix + 30 * j].odkryte2 = 1;
								if (classNieodkryte[ix + 30 * (j - 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_tekstura);
									classNieodkryte[ix + 30 * (j - 1)].odkryte2 = 1;
								}
								if (classNieodkryte[ix + 30 * (j + 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_tekstura);
									classNieodkryte[ix + 30 * (j + 1)].odkryte2 = 1;
								}
							}
							ix--;
						}
						if (classNieodkryte[ix + 30 * j].ile_sasiadów_min != 0)
						{
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * j].Nieodkryte_Pole_tekstura);
							classNieodkryte[ix + 30 * j].odkryte2 = 1;
						}
						else
						{
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[ix + 30 * j].odkryte2 = 1;
						}
					}
					if (classNieodkryte[i + 30 * j].ile_sasiadów_min != 0)
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * j].Nieodkryte_Pole_tekstura);
						classNieodkryte[i + 30 * j].odkryte2 = 1;
					}
					else
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
						classNieodkryte[ix + 30 * j].odkryte2 = 1;
					}
					// PUSTE W DÓŁ
					i = x;
					j = y;
					while ((i + 30 * j) < (i + 30 * 17) and classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
					{
						if (classNieodkryte[i + 30 * j].ile_sasiadów_min == 0)
						{
							classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[i + 30 * j].odkryte2 = 1;
						}
						j++;
						ix = x;
						while ((ix + 30 * j) < (30 + 30 * j) and classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
							{
								classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[ix + 30 * j].odkryte2 = 1;
								if (classNieodkryte[ix + 30 * (j - 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_tekstura);
									classNieodkryte[ix + 30 * (j - 1)].odkryte2 = 1;
								}
								if (classNieodkryte[ix + 30 * (j + 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_tekstura);
									classNieodkryte[ix + 30 * (j + 1)].odkryte2 = 1;
								}
							}
							ix++;
						}
						if (ix == 30)
							ix--;
						if ((ix + 30 * j) != (29 + 30 * j))
						{
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * j].Nieodkryte_Pole_tekstura);
							classNieodkryte[ix + 30 * j].odkryte2 = 1;
						}
						ix = x;
						while ((ix + 30 * j) > (30 * j) and classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
						{
							if (classNieodkryte[ix + 30 * j].ile_sasiadów_min == 0)
							{
								classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
								classNieodkryte[ix + 30 * j].odkryte2 = 1;
								if (classNieodkryte[ix + 30 * (j - 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j - 1)].Nieodkryte_Pole_tekstura);
									classNieodkryte[ix + 30 * (j - 1)].odkryte2 = 1;
								}
								if (classNieodkryte[ix + 30 * (j + 1)].ile_sasiadów_min != 0 and j != 0)
								{
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setColor(Color::White);
									classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * (j + 1)].Nieodkryte_Pole_tekstura);
									classNieodkryte[ix + 30 * (j + 1)].odkryte2 = 1;
								}
							}
							ix--;
						}
						if (classNieodkryte[ix + 30 * j].ile_sasiadów_min != 0)
						{
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[ix + 30 * j].Nieodkryte_Pole_tekstura);
							classNieodkryte[ix + 30 * j].odkryte2 = 1;
						}
						else
						{
							classNieodkryte[ix + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
							classNieodkryte[ix + 30 * j].odkryte2 = 1;
						}
					}
					if (classNieodkryte[i + 30 * j].ile_sasiadów_min != 0)
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color::White);
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setTexture(classNieodkryte[i + 30 * j].Nieodkryte_Pole_tekstura);
						classNieodkryte[i + 30 * j].odkryte2 = 1;
					}
					else
					{
						classNieodkryte[i + 30 * j].Nieodkryte_Pole_sprite.setColor(Color(100, 100, 100, 255));
						classNieodkryte[i + 30 * j].odkryte2 = 1;
					}
				}
				else if (classNieodkryte[x + 30 * y].ile_sasiadów_min == -1 and classNieodkryte[x + 30 * y].disabled == 0)
				{
					classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setColor(Color::Red);
					classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setTexture(mine);
					for (int i = 0; i < 99; i++)
					{
						if (classNieodkryte[classMines[i].nr_pola].co_tam_jest != "flaga")
						{
							classNieodkryte[classMines[i].nr_pola].Nieodkryte_Pole_sprite.setTexture(mine);
						}
						else if (classNieodkryte[classMines[i].nr_pola].co_tam_jest == "flaga")
						{
							classNieodkryte[classMines[i].nr_pola].Nieodkryte_Pole_sprite.setColor(Color::Green);
						}
					}
					for (int i = 0; i < 540; i++)
					{
						classNieodkryte[i].disabled = 1;
						koniec = 1;
					}
				}
			}
		}
		int xcd = 0;
		for (int i = 0; i < 540; i++)
		{
			if (classNieodkryte[i].co_tam_jest == "flaga" and xcd <= 99)
			{
				xcd += 1;
			}
		}
		if (Mouse::isButtonPressed(Mouse::Right))
		{
			Vector2i pos = Mouse::getPosition();
			int x = (pos.x - 429) / 35;
			int y = (pos.y - 261) / 35;
			if (x >= 0 and x <= 30 and y >= 0 and y <= 18 and classNieodkryte[x + 30 * y].ile_razy_klikniete == 0 and classNieodkryte[x + 30 * y].zajete != 1 and classNieodkryte[x + 30 * y].disabled == 0 and xcd <= 99)
			{
				classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setColor(Color::White);
				classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setTexture(flaga);
				classNieodkryte[x + 30 * y].Nieodkryte_Pole_tekstura = flaga;
				classNieodkryte[x + 30 * y].co_tam_jest = "flaga";
			}
			else if (x >= 0 and x <= 30 and y >= 0 and y <= 18 and classNieodkryte[x + 30 * y].ile_razy_klikniete == 1 and classNieodkryte[x + 30 * y].zajete != 1 and classNieodkryte[x + 30 * y].disabled == 0)
			{
				classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setTexture(nieodkryty_kwadrat);
				classNieodkryte[x + 30 * y].Nieodkryte_Pole_sprite.setColor(Color(0, 150, 200, 255));
				classNieodkryte[x + 30 * y].Nieodkryte_Pole_tekstura = nieodkryty_kwadrat;
			}
		}
		Vector2i pos = Mouse::getPosition();
		int x = (pos.x - 429) / 35;
		int y = (pos.y - 261) / 35;
		if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Right and classNieodkryte[x + 30 * y].ile_razy_klikniete == 0)
		{
			classNieodkryte[x + 30 * y].ile_razy_klikniete = 1;
		}
		else if (event.type == Event::MouseButtonReleased and event.key.code == Mouse::Right and classNieodkryte[x + 30 * y].ile_razy_klikniete == 1)
			classNieodkryte[x + 30 * y].ile_razy_klikniete = 0;
		liczba = 99;
		pom << licznik;
		pom >> liczba;
		liczba -= xcd;
		if (liczba >= 0)
		{
			pom.clear();
			pom << liczba;
			pom >> licznik;
		}
		if (liczba <= 0)
		{
			window.draw(txt1);
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::Escape)
			{
				window.close();
				break;
			}
		}
		window.display();
	}
}
