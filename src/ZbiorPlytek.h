#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Plytka.h"


using namespace std;
using namespace sf;


class ZbiorPlytek
{
	friend class RozgrywkaZAI;
	friend class Worek;
	friend class Plansza;
	friend class GraczAI;

	Plytka plytki[35];
	Texture tekstury[34];
	void wez_teksture(Texture *tekstura, int numer);

public:
	ZbiorPlytek();
	~ZbiorPlytek();
};

