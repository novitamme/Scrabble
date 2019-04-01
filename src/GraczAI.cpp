#include "GraczAI.h"


GraczAI::GraczAI(Worek *worek_pobrany, Plansza *plansza_pobrana, Slownik *slownik_pobrany, ZbiorPlytek *wszystkie_pobrane, Stojak *stojak_pobrany)
{	
	wszystkie = wszystkie_pobrane;
	worek = worek_pobrany;
	plansza = plansza_pobrana;
	slownik = slownik_pobrany;
	stojak = stojak_pobrany;

	stojak->losuj(worek);

	wynik = 0;
	pierwszy_ruch = 1;

}

GraczAI::~GraczAI()
{
}


int GraczAI::konwersja(char litera)
{
	int liczba = 0;
	for (int j = 0; j < 33; j++)  if (litera == wszystkie->plytki[j].znak) liczba = j;
	return liczba;
}

void GraczAI::poloz(NajlepszyWyraz najlepszy)
{
	int d = 0;
	
	while (najlepszy.plytki[d].znak != NULL)
	{
		if (najlepszy.orientacja == 0)
		{
			plansza->pole[najlepszy.poczatek + d][najlepszy.poziom].plytka = najlepszy.plytki[d];
			plansza->pole[najlepszy.poczatek + d][najlepszy.poziom].obraz.setTexture(wszystkie->tekstury[konwersja(najlepszy.plytki[d].znak)]);
			plansza->pole[najlepszy.poczatek + d][najlepszy.poziom].stan = 2;
			plansza->pole[najlepszy.poczatek + d][najlepszy.poziom].premia = 1;
			if (najlepszy.plytki[d].wartosc == 0) plansza->pole[najlepszy.poczatek + d][najlepszy.poziom].obraz.setColor(Color(120, 120, 120));
		}
		else
		{
			plansza->pole[najlepszy.poziom][najlepszy.poczatek + d].plytka = najlepszy.plytki[d];
			plansza->pole[najlepszy.poziom][najlepszy.poczatek + d].obraz.setTexture(wszystkie->tekstury[konwersja(najlepszy.plytki[d].znak)]);
			plansza->pole[najlepszy.poziom][najlepszy.poczatek + d].stan = 2;
			plansza->pole[najlepszy.poziom][najlepszy.poczatek + d].premia = 1;
			if (najlepszy.plytki[d].wartosc == 0) plansza->pole[najlepszy.poziom][najlepszy.poczatek + d].obraz.setColor(Color(120, 120, 120));
		}
		d++;
	}
      	for (int g = 0; g < d - 1 + pierwszy_ruch; g++)	  stojak->plytka[najlepszy.ubyte_plytki[g]].znak = NULL;
	wynik = wynik + najlepszy.punkty;
}

int GraczAI::pierwsza_ostatnia(Vector2i wspolrzedne, int kierunek, int dziura)
{
	int wynik = 0;

	for (int e = 0; e < stojak->stan; e++)
	{
		if ((plansza->pole[wspolrzedne.x + 2 * kierunek][wspolrzedne.y].plytka.znak != 32 && wspolrzedne.x != dziura) || (plansza->pole[wspolrzedne.x + 1 * kierunek][wspolrzedne.y - 1].plytka.znak != 32 && wspolrzedne.y != 2) || (plansza->pole[wspolrzedne.x + 1 * kierunek][wspolrzedne.y + 1].plytka.znak != 32 && wspolrzedne.y != 16)) e = 6;
		else wspolrzedne.x = wspolrzedne.x + kierunek;
	}
	wynik = wspolrzedne.x;
	return wynik;
}

void GraczAI::kombinacja(Vector2i wspolrzedne, int poczatek, int koniec, NajlepszyWyraz *najlepszy)
{
	int zbior[7] = { 0,1,2,3,4,5,6 };
	Plytka aktualna[10];
	bool koncz = 0;
	int b = 0;
	do
	{
		do
		{
			int blank1 = 1;
			int blank_gdzie1 = 0;
			int blank2 = 1;
			int blank_gdzie2 = 0;
			b = 0;

			for (int q = 0; q <= koniec - poczatek; q++)
			{
				if (q == wspolrzedne.x - poczatek)
				{
					aktualna[q].znak = plansza->pole[wspolrzedne.x][wspolrzedne.y].plytka.znak;
					aktualna[q].wartosc = plansza->pole[wspolrzedne.x][wspolrzedne.y].plytka.wartosc;
				}
				else
				{
					aktualna[q] = stojak->plytka[zbior[b]];
					b++;
				}
				if (aktualna[q].znak == 63 && blank1 == 32)
				{
					aktualna[q].wartosc = 0;
					blank_gdzie2 = q;
					blank2 = 32;
				}
				if (aktualna[q].znak == 63 && blank2 == 1)
				{
					aktualna[q].wartosc = 0;
					blank_gdzie1 = q;
					blank1 = 32;
				}
			}
			aktualna[koniec - poczatek + 1].znak = NULL;
			aktualna[koniec - poczatek + 1].wartosc = NULL;
			////////////////////////////////////////////////////////////////////////////////
			for (int r = 0; r < blank2; r++)
			{
				if (blank2 == 32)	aktualna[blank_gdzie2].znak = wszystkie->plytki[r].znak;
				for (int h = 0; h < blank1; h++)
				{
					if (blank1 == 32)	aktualna[blank_gdzie1].znak = wszystkie->plytki[h].znak;
					if (slownik->sprawdz(aktualna) == 1)
					{
						if (podlicz(plansza, aktualna, wspolrzedne.y, poczatek, koniec, 1, pierwszy_ruch) > najlepszy->punkty)
						{
							for (int d = 0; d <= koniec - poczatek; d++)	najlepszy->plytki[d] = aktualna[d];
							for (int r = 0; r < koniec - poczatek + pierwszy_ruch; r++)	najlepszy->ubyte_plytki[r] = zbior[r];
							najlepszy->ubyte_plytki[koniec - poczatek + pierwszy_ruch] = NULL;
							najlepszy->plytki[koniec - poczatek + 1].znak = NULL;
							najlepszy->punkty = podlicz(plansza, aktualna, wspolrzedne.y, poczatek, koniec, 1, pierwszy_ruch);
							najlepszy->poczatek = poczatek;
							najlepszy->poziom = wspolrzedne.y;
							najlepszy->orientacja = orientacja;
						}
					}
				}
			}

		} while (next_permutation(zbior, zbior + koniec - poczatek + pierwszy_ruch));

		//////////////////////////////////kombinacja////////////////////////////////////
		if (zbior[0] == stojak->stan - koniec + poczatek - pierwszy_ruch) koncz = 1;

		for (int a = koniec - poczatek + pierwszy_ruch; a > 0; a--)
		{
			if (zbior[a - 1] != (a - koniec + poczatek + stojak->stan - 1 - pierwszy_ruch))
			{
				zbior[a - 1] = zbior[a - 1] + 1;
				a = 1;
			}
			else
			{
				int t = 1;
				for (int s = a; s <= koniec - poczatek + pierwszy_ruch; s++)
				{
					zbior[s - 1] = zbior[s - 2] + 1 + t;
					t = 0;
				}
			}
		}
		//////////////////////////////////kombinacja////////////////////////////////////
	} while (koncz == 0);
}

void GraczAI::stopien1(Vector2i wspolrzedne, NajlepszyWyraz *najlepszy)
{
	int poczatek = 0, koniec = 0, dlugosc = 0, zajete = 0;

	if ((plansza->pole[wspolrzedne.x - 1][wspolrzedne.y].plytka.znak == 32 || wspolrzedne.x == 2) && (plansza->pole[wspolrzedne.x + 1][wspolrzedne.y].plytka.znak == 32 || wspolrzedne.x == 16))
	{
		poczatek = pierwsza_ostatnia(wspolrzedne, -1, 3);
		koniec = pierwsza_ostatnia(wspolrzedne, 1, 15);

		for (int p = poczatek; p <= wspolrzedne.x; p++)
		{
			for (int k = wspolrzedne.x; k <= koniec; k++)
			{
				if (k - p > 0 && k - p <= stojak->stan)
				{
					kombinacja(wspolrzedne, p, k, najlepszy);
				}
			}
		}
	}
}

void GraczAI::szukaj()
{
	NajlepszyWyraz najlepszy;

	for (int m = 0; m <= 1; m++)
	{
		orientacja = m;
		if (pierwszy_ruch == 1)
		{
			int x = 100;
			int y = 9;
			for (int p = 3; p <= 9; p++)
			{
				for (int k = 9; k <= 15; k++)
				{
					if (k - p > 1 && k - p < 7)
					{
						kombinacja(Vector2i(x, y), p, k, &najlepszy);
					}
				}
			}
		}
		else
		{
			for (int y = 2; y < 17; y++)
			{
				for (int x = 2; x < 17; x++)
				{
					if (plansza->pole[x][y].plytka.znak != 32)
					{
						stopien1(Vector2i(x, y), &najlepszy);
					}
				}
			}
		}
		plansza->przerzut_planszy(m);
	}

	poloz(najlepszy);
	pierwszy_ruch = 0;
}