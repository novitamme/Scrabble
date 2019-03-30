#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Podniesiona_plytka
{
	friend class RozgrywkaZAI;

	Vector2i wspolrzedne;
	Vector2i bufor_kursora;
	int numer_plytki;


public:
	Podniesiona_plytka();
	~Podniesiona_plytka();
};

