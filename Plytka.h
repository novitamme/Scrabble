#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Plytka
{
	friend class ZbiorPlytek;
	friend class RozgrywkaZAI;
	friend class Stojak;
	friend class Plansza;
	friend class Slownik;
	friend class GraczAI;
	friend class Gracz;


	char znak;
	int wartosc;

public:
	Plytka();
	~Plytka();
};

