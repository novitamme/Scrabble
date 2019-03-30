#include "Plansza.h"


Plansza::Plansza(float rozmiar_okna, float rozmiar_plytki, ZbiorPlytek zbior)
{
	tekstura.loadFromFile("plansza.jpg");
	obraz.setTexture(tekstura);
	float skala_planszy = (rozmiar_okna - 50) / tekstura.getSize().y;
	obraz.setScale(Vector2f (skala_planszy, skala_planszy));
	obraz.setPosition(25,25);

	pusta_tekstura.loadFromFile("pusta.png");

	float skala_pola = (rozmiar_okna - 50) / (15 * (rozmiar_plytki + 2));
	for (int i = 2; i < 17; i++) for (int j = 2; j < 17; j++)
	{
		pole[i][j].obraz.setPosition( 26 + (i-2) * (rozmiar_okna - 50) / 15, 26 + (j-2) * (rozmiar_okna - 50) / 15);
		pole[i][j].obraz.setScale(skala_pola ,skala_pola);
		pole[i][j].obraz.setTexture(pusta_tekstura);
	}

	nadaj_wartosci(zbior);
}

Plansza::~Plansza()
{
}

void Plansza::nadaj_wartosci(ZbiorPlytek zbior)
{
	for (int y = 0; y < 19; y++)
	{
		for (int x = 0; x < 19; x++)
		{
			pole[x][y].plytka = zbior.plytki[34];
		}
	}

	for (int y = 2; y < 17; y++)
	{
		for (int x = 2; x < 17; x++)
		{
			pole[x][y].plytka = zbior.plytki[33];
		}
	}

	fstream plik_z_danymi;
	char wart[1];
	plik_z_danymi.open("premie.txt", ios_base::in);

	for (int y = 2; y < 17; y++)
	{
		for (int x = 2; x < 17; x++)
		{
			plik_z_danymi.read(wart, 1);
			pole[x][y].premia = wart[0] - 96;
		}
		plik_z_danymi.seekg(2, ios_base::cur);
	}
}

void Plansza::przerzut_planszy(int kierunek)
{
	Pole zastêpcze[19][19];

	if (kierunek == 0)  for (int y = 0; y < 19; y++)  for (int x = 0; x < 19; x++)  zastêpcze[x][y] = pole[y][x];

	else  for (int y = 18; y >= 0; y--)  for (int x = 0; x < 19; x++)  zastêpcze[x][y] = pole[y][x];

	for (int y = 0; y < 19; y++)  for (int x = 0; x < 19; x++)  pole[x][y] = zastêpcze[x][y];

	//delete zastêpcze;
}