#include "Przycisk.h"


Przycisk::Przycisk(int wymiar_odniesienia)
{
	faza = 0;

	tekstura.loadFromFile("ok.jpg");

	obraz.setTexture(tekstura);

	polozenie.x = wymiar_odniesienia + 100;
	polozenie.y = 220;

	obraz.setPosition(polozenie);
}

Przycisk::~Przycisk()
{
}


void Przycisk::uaktywnij(bool ruch_gracza)
{
	if (ruch_gracza == 0) aktywny = 0;

	if (aktywny == 1) obraz.setColor(Color(Color::White));
	else obraz.setColor(Color(120, 120, 120));
}

void Przycisk::ruch_wciskania()
{
	if (faza == 1)
	{
		polozenie.x += 2;
		polozenie.y += 2;
		faza = 2;
		obraz.setPosition(polozenie);
	}
	else if (faza == 2)
	{
		polozenie.x -= 2;
		polozenie.y -= 2;
		faza = 0;
		obraz.setPosition(polozenie);
	}
}