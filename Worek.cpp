#include "Worek.h"


Worek::Worek(ZbiorPlytek zbior)
{
	stan = 100;

	fstream plik_z_danymi;
	char odczyt[1];
	int ilosc_wystapien;
	int q = 0;

	plik_z_danymi.open("wystap.txt", ios_base::in);

	for (int h = 0; h < 33; h++)
	{
		plik_z_danymi.read(odczyt, 1);

		ilosc_wystapien = odczyt[0] - 96;

		for (int b = 0; b < ilosc_wystapien; b++)
		{
			plytki[q] = zbior.plytki[h];
			tekstury[q] = zbior.tekstury[h];
			q++;
		}
	}
}

Worek::~Worek()
{
}
