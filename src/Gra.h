#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "RozgrywkaZAI.h"
#include "ZbiorPlytek.h"
#include "Slownik.h"

using namespace std;
using namespace sf;


class Gra
{

	Texture tekstura_loga;
	Sprite logo;
	
public:
	Gra();
	~Gra();
};

