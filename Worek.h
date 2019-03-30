#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Plytka.h"
#include "ZbiorPlytek.h"

using namespace std;
using namespace sf;


class Worek
{
	friend class RozgrywkaZAI;
	friend class Stojak;

	Plytka plytki[100];
	Texture tekstury[100];
	int stan;

public:
	Worek(ZbiorPlytek zbior);
	~Worek();
};