#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plytka.h"

using namespace std;
using namespace sf;

class Pole
{
	friend class RozgrywkaZAI;
	friend class Plansza;
	friend class GraczAI;
	friend class Gracz;
	
	Texture tekstura;
	Sprite obraz;
	Plytka plytka;
	int premia;
	int stan;
	int zrodlo_plytki;

public:
	Pole();
	~Pole();
};

