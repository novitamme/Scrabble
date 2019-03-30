#include "Gracz.h"


Gracz::Gracz(Stojak *stojak_pobrany)
{
	stojak = stojak_pobrany;
	wynik = 0;
}

Gracz::~Gracz()
{
}

int Gracz::podlicz(Plansza *plansza, Plytka wyraz[], int wspolrzedna_y, int poczatek, int koniec, int ruch_komputera, int pierwszy_ruch)
{
	int suma = 0, nr_litery = 0, mnoznik = 1;

	for (int v = poczatek; v <= koniec; v++)
	{
		if (plansza->pole[v][wspolrzedna_y].premia <= 3) suma = suma + wyraz[nr_litery].wartosc * plansza->pole[v][wspolrzedna_y].premia;
		if (plansza->pole[v][wspolrzedna_y].premia == 4)
		{
			suma = suma + wyraz[nr_litery].wartosc;
			mnoznik = mnoznik * 2;
		}
		if (plansza->pole[v][wspolrzedna_y].premia == 5)
		{
			suma = suma + wyraz[nr_litery].wartosc;
			mnoznik = mnoznik * 3;
		}
		nr_litery++;
	}
	suma = suma * mnoznik;

	if (ruch_komputera == 1)
	{
		if (nr_litery == 8 - pierwszy_ruch) suma += 50;
	}
	return suma;
}




