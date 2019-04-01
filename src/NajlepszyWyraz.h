#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Plytka.h"

using namespace std;
using namespace sf;


class NajlepszyWyraz
{
	friend class GraczAI;

	Plytka plytki[10];
	int ubyte_plytki[7];
	bool orientacja;
	int poczatek;
	int poziom;
	int punkty;

public:
	NajlepszyWyraz();
	~NajlepszyWyraz();
};

