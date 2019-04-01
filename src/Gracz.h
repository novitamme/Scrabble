#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Stojak.h"
#include "Plansza.h"

using namespace std;
using namespace sf;


class Gracz
{
	friend class RozgrywkaZAI;
	friend class GraczAI;

	Plansza* plansza;
	Stojak *stojak;
	int wynik;

	int podlicz(Plansza *plansza, Plytka wyraz[], int wspolrzedna_y, int poczatek, int koniec, int ruch_komputera, int pierwszy_ruch);


public:
	Gracz(Stojak *stojak_pobrany = NULL);
	~Gracz();
};

