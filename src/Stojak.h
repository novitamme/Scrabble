#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plytka.h"
#include "Worek.h"
#include "ZbiorPlytek.h"

using namespace std;
using namespace sf;


class Stojak
{
	friend class RozgrywkaZAI;
	friend class GraczAI;
	friend class Gracz;

	Sprite obraz;
	Texture tekstura;
	Texture pusta_tekstura;

	Sprite obraz_plytki[7];
	Plytka plytka[7];
	Texture tekstury[7];
	int stan;

	void losuj(Worek *worek);

public:
	Stojak(Vector2u rozmiar_okna, bool czyj);
	~Stojak();
};

