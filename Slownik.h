#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Wezel.h"
#include "Plytka.h"

using namespace std;
using namespace sf;

class Slownik
{
	friend class GraczAI;
	friend class RozgrywkaZAI;

	Wezel glowny;
	Wezel *wskaznik = &glowny;

	int numeracja(char litera);
	bool sprawdz(Plytka slowo[]);

public:
	Slownik();
	~Slownik();
};

