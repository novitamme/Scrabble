#include "Slownik.h"


Slownik::Slownik()
{
	fstream plik;
	char lit[1];
	int numer;
	Wezel* aktualny = wskaznik;
	aktualny->czy_istnieje = 0;
	plik.open("bazakrotka.txt", ios::in);

	while (plik.eof() != 1)
	{
		plik.read(lit, 1);
		while (lit[0] != 10)
		{
			numer = numeracja(lit[0]);
			if (aktualny->galaz[numer] == nullptr)
			{
				aktualny->galaz[numer] = new Wezel;
				aktualny = aktualny->galaz[numer];
			}
			else aktualny = aktualny->galaz[numer];
			plik.read(lit, 1);
		}
		aktualny->czy_istnieje = 1;
		aktualny = wskaznik;
	}
}

Slownik::~Slownik()
{
}

int Slownik::numeracja(char litera)
{
	int liczba = 0;
	if (litera < 113) liczba = litera - 88;
	if (litera > 113 && litera < 118) liczba = litera - 89;
	if (litera == 119) liczba = litera - 90;
	if (litera > 120) liczba = litera - 91;
	return liczba;
}

bool Slownik::sprawdz(Plytka slowo[])
{
	Wezel* aktualny = wskaznik;
	int o = 0;
	bool zly = 0;
	char slowo1[10];
	for (int g = 0; g < 10; g++) slowo1[g] = slowo[g].znak;

	while (slowo1[o] != NULL)
	{
		int numer = numeracja(slowo1[o]);
		if (aktualny->galaz[numer] == nullptr)
		{
			slowo1[o + 1] = NULL;
			zly = 1;
		}
		else
		{
			aktualny = aktualny->galaz[numer];
			zly = 0;
		}
		o++;
	}
	if (aktualny->czy_istnieje == 1 && zly == 0) return 1;
	else return 0;
}