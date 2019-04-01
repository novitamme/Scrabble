#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Plytka.h"
#include "Worek.h"
#include "Stojak.h"
#include "Plansza.h"
#include "Pole.h"
#include "GraczAI.h"
#include "Gracz.h"
#include "Podniesiona_plytka.h"
#include "Przycisk.h"
#include "Wyniki.h"

using namespace std;
using namespace sf;


class RozgrywkaZAI
{
	Worek *worek;
	Plansza *plansza;
	RenderWindow *okno;
	GraczAI *komputer;
	Gracz *gracz;
	Slownik *slownik;
	Przycisk *ok;
	ZbiorPlytek *wszystkie;

	Wyniki* tablica_wynikow;
	Texture tekstura_tab_blanka;
	Sprite tablica_blanka;
	Texture pusta_tekstura;
	Vector2i pozycja_myszy;
	Event akcja;
	Podniesiona_plytka podniesiona_plytka;
	bool gra_trwa;
	bool ruch_gracza;
	bool czy_podniesiona_plytka;
	bool zdefiniuj_blanka;
	int numer_ruchu;

	void koniec_gry(bool kto_skonczyl);
	bool zatwierdz_slowo(int *punkty);
	void koniec_ruchu();
	bool czy_poprawnie_lezy();
	void mieszanie_stojaka(int pierwsza, int druga);
	void obsluga_myszy();
	void petla_glowna();

public:
	RozgrywkaZAI(RenderWindow *okno_z, ZbiorPlytek *wszystkie_pobrane, Slownik *slownik_pobrany);
	~RozgrywkaZAI();
};

