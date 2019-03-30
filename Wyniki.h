#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Wyniki
{
	friend class RozgrywkaZAI;

	Font czcionka;
	Text pola_tekstowe[2];
	Wyniki* kolejny_wynik;

public:
	Wyniki(int polozenie_x, int numer_ruchu, string wynik_jednostkowy, string suma_punktow);
	~Wyniki();
};

