#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class Przycisk
{
	friend class RozgrywkaZAI;

	Texture tekstura;
	Sprite obraz;
	Vector2f polozenie;
	bool aktywny;
	int faza;

	void uaktywnij(bool ruch_gracza);
	void ruch_wciskania();

public:
	Przycisk(int wymiar_odniesienia);
	~Przycisk();
};

