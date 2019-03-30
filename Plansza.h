#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Pole.h"
#include "ZbiorPlytek.h"

using namespace std;
using namespace sf;


class Plansza
{
	friend class RozgrywkaZAI;
	friend class GraczAI;
	friend class Gracz;

	Texture pusta_tekstura;
	Texture tekstura;
	Sprite obraz;
	Pole pole[19][19];

	void nadaj_wartosci(ZbiorPlytek zbior);
	void przerzut_planszy(int kierunek);

public:
	Plansza(float rozmiar_okna, float rozmiar_plytki, ZbiorPlytek zbior);
	~Plansza();
};

