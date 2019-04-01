#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Stojak.h"
#include "Slownik.h"
#include "Plansza.h"
#include "NajlepszyWyraz.h"
#include "Gracz.h"

using namespace std;
using namespace sf;


class GraczAI
	:public Gracz
{
	friend class RozgrywkaZAI;

	bool pierwszy_ruch;
	bool orientacja;
	ZbiorPlytek *wszystkie;
	Worek *worek;
	Slownik *slownik;
	Plansza *plansza;

	int konwersja(char litera);
	void poloz(NajlepszyWyraz najlepszy);
	int pierwsza_ostatnia(Vector2i wspolrzedne, int kierunek, int dziura);
	void kombinacja(Vector2i wspolrzedne, int poczatek, int koniec, NajlepszyWyraz *najlepszy);
	void stopien1(Vector2i wspolrzedne, NajlepszyWyraz *najlepszy);
	void szukaj();

public:
	GraczAI(Worek *worek_pobrany, Plansza *plansza_pobrana, Slownik *slownik_pobrany, ZbiorPlytek *wszystkie_pobrane, Stojak *stojak_pobrany);
	~GraczAI();
};

