#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Wezel
{
	friend class Slownik;

	Wezel *galaz[32];
	bool czy_istnieje;

public:
	Wezel();
	~Wezel();
};

