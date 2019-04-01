#include "Wyniki.h"


Wyniki::Wyniki(int polozenie_x, int numer_ruchu, string wynik_jednostkowy, string suma_punktow)
{
	kolejny_wynik = nullptr;

	czcionka.loadFromFile("sansation.ttf");

	for (int b = 0; b < 2; b++)
	{
		pola_tekstowe[b].setFont(czcionka);
		pola_tekstowe[b].setCharacterSize(20);
		pola_tekstowe[b].setColor(Color::White);
	}

	pola_tekstowe[0].setPosition(polozenie_x + 100 + (numer_ruchu % 2) * 150, 300 + (numer_ruchu / 2) * 25);
	pola_tekstowe[1].setPosition(polozenie_x + 150 + (numer_ruchu % 2) * 150, 300 + (numer_ruchu / 2) * 25);

	pola_tekstowe[0].setString(wynik_jednostkowy);
	pola_tekstowe[1].setString(suma_punktow);
}

Wyniki::~Wyniki()
{
}
