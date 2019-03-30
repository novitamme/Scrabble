#include "ZbiorPlytek.h"

ZbiorPlytek::ZbiorPlytek()
{
	fstream plik_z_danymi;
	char odczyt[3];
	
	plik_z_danymi.open("znaki_i_wartosci.txt", ios_base::in);

	for (int h = 0; h < 33; h++)
	{
		plik_z_danymi.read(odczyt, 3);

		plytki[h].znak = odczyt[0];
		plytki[h].wartosc = odczyt[1] - 96;
		
		Texture zastepcza;
		wez_teksture(&zastepcza, h);
		tekstury[h] = zastepcza;
	}
	plik_z_danymi.close();

	plytki[33].znak = 32;
	plytki[33].wartosc = NULL;

	plytki[34].znak = 30;
	plytki[34].wartosc = NULL;
}

ZbiorPlytek::~ZbiorPlytek()
{
}

void ZbiorPlytek::wez_teksture(Texture *tekstura, int numer)
{
	if (numer == 0) tekstura->loadFromFile("literaa.jpg");
	else if (numer == 1) tekstura->loadFromFile("literaom.jpg");
	else if (numer == 2) tekstura->loadFromFile("literab.jpg");
	else if (numer == 3) tekstura->loadFromFile("literac.jpg");
	else if (numer == 4) tekstura->loadFromFile("literaci.jpg");
	else if (numer == 5) tekstura->loadFromFile("literad.jpg");
	else if (numer == 6) tekstura->loadFromFile("literae.jpg");
	else if (numer == 7) tekstura->loadFromFile("literaem.jpg");
	else if (numer == 8) tekstura->loadFromFile("literaf.jpg");
	else if (numer == 9) tekstura->loadFromFile("literag.jpg");
	else if (numer == 10) tekstura->loadFromFile("literah.jpg");
	else if (numer == 11) tekstura->loadFromFile("literai.jpg");
	else if (numer == 12) tekstura->loadFromFile("literaj.jpg");
	else if (numer == 13) tekstura->loadFromFile("literak.jpg");
	else if (numer == 14) tekstura->loadFromFile("literal.jpg");
	else if (numer == 15) tekstura->loadFromFile("literaeu.jpg");
	else if (numer == 16) tekstura->loadFromFile("literam.jpg");
	else if (numer == 17) tekstura->loadFromFile("literan.jpg");
	else if (numer == 18) tekstura->loadFromFile("literani.jpg");
	else if (numer == 19) tekstura->loadFromFile("literao.jpg");
	else if (numer == 20) tekstura->loadFromFile("literaou.jpg");
	else if (numer == 21) tekstura->loadFromFile("literap.jpg");
	else if (numer == 22) tekstura->loadFromFile("literar.jpg");
	else if (numer == 23) tekstura->loadFromFile("literas.jpg");
	else if (numer == 24) tekstura->loadFromFile("literasi.jpg");
	else if (numer == 25) tekstura->loadFromFile("literat.jpg");
	else if (numer == 26) tekstura->loadFromFile("literau.jpg");
	else if (numer == 27) tekstura->loadFromFile("literaw.jpg");
	else if (numer == 28) tekstura->loadFromFile("literay.jpg");
	else if (numer == 29) tekstura->loadFromFile("literaz.jpg");
	else if (numer == 30) tekstura->loadFromFile("literazi.jpg");
	else if (numer == 31) tekstura->loadFromFile("literarz.jpg");
	else if (numer == 32) tekstura->loadFromFile("literabl.jpg");
}
