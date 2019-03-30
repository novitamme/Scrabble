#include "RozgrywkaZAI.h"


RozgrywkaZAI::RozgrywkaZAI(RenderWindow *okno_z, ZbiorPlytek *wszystkie_pobrane, Slownik *slownik_pobrany)
{
	okno = okno_z;
    
	wszystkie = wszystkie_pobrane;

 	Worek worek_z(*wszystkie);
	worek = &worek_z;

	slownik = slownik_pobrany;

	Plansza plansza_z(okno->getSize().y, wszystkie->tekstury[0].getSize().y, *wszystkie);
	plansza = &plansza_z;

	Stojak stojak_g(okno->getSize(), 1);
	Gracz gracz_z(&stojak_g);
	gracz = &gracz_z;

	gracz->stojak->losuj(worek);

	Stojak stojak_k(Vector2u(100, 900), 0);
	GraczAI komputer_z(worek, plansza, slownik, wszystkie, &stojak_k);
	komputer = &komputer_z;

	pusta_tekstura.loadFromFile("pusta.png");

	Przycisk ok_z(okno->getSize().y);
	ok = &ok_z;

	tekstura_tab_blanka.loadFromFile("blank.jpg");
	tablica_blanka.setTexture(tekstura_tab_blanka);
	tablica_blanka.setPosition(okno->getSize().y + 100, 220);

	gra_trwa = 1;
	czy_podniesiona_plytka = 0;
	zdefiniuj_blanka = 0;
	ruch_gracza = (rand() % 2);
	cout << ruch_gracza;
	numer_ruchu = 2;

	tablica_wynikow = new Wyniki(okno->getSize().y, ruch_gracza, "    Komputer", " ");
	tablica_wynikow->kolejny_wynik = new Wyniki(okno->getSize().y, !ruch_gracza, "    Ja", " ");

	petla_glowna();
}

RozgrywkaZAI::~RozgrywkaZAI()
{
}


void RozgrywkaZAI::koniec_gry(bool kto_skonczyl)
{
	int punkty_odpisu = 0;
	if (kto_skonczyl == 0) for (int i = 0; i < 7; i++) if (gracz->stojak->plytka[i].znak == NULL) punkty_odpisu += gracz->stojak->plytka[i].wartosc;
	if (kto_skonczyl == 1) for (int i = 0; i < 7; i++) if (komputer->stojak->plytka[i].znak == NULL) punkty_odpisu += komputer->stojak->plytka[i].wartosc;

	if (numer_ruchu % 2 == 1) numer_ruchu++;

	if (kto_skonczyl == 0) punkty_odpisu *= (-1);

	komputer->wynik -= punkty_odpisu;
	gracz->wynik += punkty_odpisu;


	Wyniki *wskaznik_do_wynikow = tablica_wynikow;  
	while (wskaznik_do_wynikow->kolejny_wynik != nullptr)  wskaznik_do_wynikow = wskaznik_do_wynikow->kolejny_wynik;
	wskaznik_do_wynikow->kolejny_wynik = new Wyniki(okno->getSize().y, numer_ruchu, to_string(-punkty_odpisu), to_string(komputer->wynik));
	wskaznik_do_wynikow->kolejny_wynik->kolejny_wynik = new Wyniki(okno->getSize().y, numer_ruchu + 1, to_string(punkty_odpisu), to_string(gracz->wynik));

	gra_trwa = 0;
}

bool RozgrywkaZAI::zatwierdz_slowo(int *punkty)
{
	bool poprawne = 1;
	for (int p = 0; p <= 1; p++)
	{
		for (int g = 2; g < 17; g++)  for (int f = 2; f < 17; f++)  if (plansza->pole[f][g].stan == 1)
		{
			Plytka slowo[15];
			int poczatek_slowa = f, numer_litery = 0;
			while (plansza->pole[poczatek_slowa - 1][g].stan != 0) poczatek_slowa--;
			f = poczatek_slowa;
			while (plansza->pole[f][g].stan != 0)
			{
				slowo[numer_litery] = plansza->pole[f][g].plytka;
				numer_litery++;
				f++;
			}
			f--;
			slowo[numer_litery].znak = NULL;
			if (numer_litery > 1)
			{
				if (slownik->sprawdz(slowo) == 0) 	poprawne = 0;
				*punkty = *punkty + gracz->podlicz(plansza, slowo, g, poczatek_slowa, f, 0, 0);
			}
		}
		plansza->przerzut_planszy(p);
	}
	return poprawne;
}

void RozgrywkaZAI::koniec_ruchu()
{
	for (int f = 2; f < 17; f++)  for (int g = 2; g < 17; g++)  if (plansza->pole[f][g].plytka.znak == 63) zdefiniuj_blanka = 1;

	if (zdefiniuj_blanka == 0)
	{
		int punkty = 0;
		if (zatwierdz_slowo(&punkty) == 1)
		{
			int premia = 50;
			for (int i = 0; i < 7; i++) if (gracz->stojak->plytka[i].znak != NULL) premia = 0;
			if (gracz->stojak->stan < 7) premia = 0;
			punkty += premia;

			for (int f = 2; f < 17; f++)  for (int g = 2; g < 17; g++)  if (plansza->pole[f][g].stan == 1)
			{
				plansza->pole[f][g].stan = 2;
				plansza->pole[f][g].premia = 1;
			}
			gracz->stojak->losuj(worek);
		}
		else
		{
			for (int i = 2; i < 17; i++)  for (int j = 2; j < 17; j++)  if (plansza->pole[i][j].stan == 1)
			{
				if (plansza->pole[i][j].plytka.wartosc == 0)
				{
					gracz->stojak->obraz_plytki[plansza->pole[i][j].zrodlo_plytki].setTexture(wszystkie->tekstury[32]);
					gracz->stojak->plytka[plansza->pole[i][j].zrodlo_plytki].znak = 63;
					plansza->pole[i][j].obraz.setColor(Color(Color::White));
				}
				else
				{
					gracz->stojak->obraz_plytki[plansza->pole[i][j].zrodlo_plytki].setTexture(gracz->stojak->tekstury[plansza->pole[i][j].zrodlo_plytki]);
					gracz->stojak->plytka[plansza->pole[i][j].zrodlo_plytki] = plansza->pole[i][j].plytka;
				}
				plansza->pole[i][j].obraz.setTexture(pusta_tekstura);
				plansza->pole[i][j].plytka.znak = 32;
				plansza->pole[i][j].stan = 0;
			}
			punkty = 0;
		}
		gracz->wynik += punkty;
		Wyniki *wskaznik_do_wynikow = tablica_wynikow;
		while (wskaznik_do_wynikow->kolejny_wynik != nullptr) wskaznik_do_wynikow = wskaznik_do_wynikow->kolejny_wynik;
		wskaznik_do_wynikow->kolejny_wynik = new Wyniki(okno->getSize().y, numer_ruchu, to_string(punkty), to_string(gracz->wynik));
		numer_ruchu++;
		ruch_gracza = 0;
	}
	if (gracz->stojak->plytka[0].znak == NULL  && zdefiniuj_blanka == 0) koniec_gry(1);
}

bool RozgrywkaZAI::czy_poprawnie_lezy()
{
	Vector2i wspolrzedne[7];
	int wylozone_plytki = 0;
	bool poprawnie = 0;

	for (int f = 2; f < 17; f++)  for (int g = 2; g < 17; g++)  if (plansza->pole[f][g].stan == 1)
	{
		for (int i = -1; i <= 1; i += 2)  if (plansza->pole[f + i][g].stan == 2 || plansza->pole[f][g + i].stan == 2) poprawnie = 1;
		wspolrzedne[wylozone_plytki] = Vector2i(f, g);
		wylozone_plytki++;
	}
	if(wylozone_plytki > 1 && ( poprawnie == 1 || plansza->pole[9][9].stan != 2))
	{
		poprawnie = 1;
		bool pion = 1, poziom = 1;
		for (int i = 1; i < wylozone_plytki; i++)  if (wspolrzedne[i].x != wspolrzedne[0].x) pion = 0;
		for (int i = 1; i < wylozone_plytki; i++)  if (wspolrzedne[i].y != wspolrzedne[0].y) poziom = 0;
	
		if ((pion == 0 && poziom == 0) || (pion == 1 && poziom == 1)) poprawnie = 0;
		else
		{
			for (int i = 1; i < wylozone_plytki; i++)
			{
				if (plansza->pole[wspolrzedne[0].x + i * poziom][wspolrzedne[0].y + i * pion].stan == 0) poprawnie = 0;
				if (plansza->pole[wspolrzedne[0].x + i * poziom][wspolrzedne[0].y + i * pion].stan == 2) wylozone_plytki++;
			}
		}
	}
	if (plansza->pole[9][9].stan == 0) poprawnie = 0;
	return poprawnie;
}

void RozgrywkaZAI::mieszanie_stojaka(int pierwsza, int druga)
{
	Plytka p_zastepcza;
	Texture t_zastepcza;

	int kierunek = 1;
	int bufor_nieobecnej_plytki = 0;
	if (pierwsza > druga)  kierunek = -1;
    p_zastepcza = gracz->stojak->plytka[pierwsza];
	t_zastepcza = gracz->stojak->tekstury[pierwsza];

	for (int g = pierwsza; g*kierunek < druga*kierunek; g = g + kierunek)
	{
		while (gracz->stojak->plytka[g + kierunek + bufor_nieobecnej_plytki].znak == NULL) bufor_nieobecnej_plytki += kierunek;
		gracz->stojak->plytka[g] = gracz->stojak->plytka[g + kierunek + bufor_nieobecnej_plytki];
		gracz->stojak->tekstury[g] = gracz->stojak->tekstury[g + kierunek + bufor_nieobecnej_plytki];
		gracz->stojak->obraz_plytki[g].setTexture(gracz->stojak->tekstury[g]);
		g += bufor_nieobecnej_plytki;
		bufor_nieobecnej_plytki = 0;
	}

	gracz->stojak->plytka[druga] = p_zastepcza;
	gracz->stojak->tekstury[druga] = t_zastepcza;
}

void RozgrywkaZAI::obsluga_myszy()
{
	Vector2f pozycja_mysz = (Vector2f(pozycja_myszy.x, pozycja_myszy.y));

	if (zdefiniuj_blanka == 0)
	{
		if (czy_podniesiona_plytka == 0)
		{
			for (int i = 0; i < 7; i++) if (gracz->stojak->obraz_plytki[i].getGlobalBounds().contains(pozycja_mysz) && gracz->stojak->plytka[i].znak != NULL)
			{
				podniesiona_plytka.wspolrzedne = Vector2i(gracz->stojak->obraz_plytki[i].getPosition().x, gracz->stojak->obraz_plytki[i].getPosition().y);
				podniesiona_plytka.bufor_kursora = Vector2i(pozycja_mysz.x - gracz->stojak->obraz_plytki[i].getPosition().x, pozycja_mysz.y - gracz->stojak->obraz_plytki[i].getPosition().y);
				podniesiona_plytka.numer_plytki = i;
				czy_podniesiona_plytka = 1;
			}

			for (int i = 2; i < 17; i++) for (int j = 2; j < 17; j++) if (plansza->pole[i][j].obraz.getGlobalBounds().contains(pozycja_mysz))
			{
				if (plansza->pole[i][j].stan == 1)
				{
					gracz->stojak->obraz_plytki[plansza->pole[i][j].zrodlo_plytki].setTexture(gracz->stojak->tekstury[plansza->pole[i][j].zrodlo_plytki]);
					plansza->pole[i][j].obraz.setTexture(pusta_tekstura);
					gracz->stojak->plytka[plansza->pole[i][j].zrodlo_plytki] = plansza->pole[i][j].plytka;
					plansza->pole[i][j].plytka.znak = 32;
					plansza->pole[i][j].stan = 0;
				}

				else if (plansza->pole[i][j].stan == 0)
				{
					int najblizsza_plytka = 8;
					for (int i = 0; i < 7; i++) if (gracz->stojak->plytka[i].znak != NULL)
					{
						najblizsza_plytka = i;
						i = 7;
					}
					if (najblizsza_plytka != 8)
					{
						plansza->pole[i][j].tekstura = gracz->stojak->tekstury[najblizsza_plytka];
						plansza->pole[i][j].obraz.setTexture(plansza->pole[i][j].tekstura);
						gracz->stojak->obraz_plytki[najblizsza_plytka].setTexture(pusta_tekstura);
						plansza->pole[i][j].plytka = gracz->stojak->plytka[najblizsza_plytka];
						gracz->stojak->plytka[najblizsza_plytka].znak = NULL;
						plansza->pole[i][j].stan = 1;
						plansza->pole[i][j].zrodlo_plytki = najblizsza_plytka;
					}
				}
			}
		}

		else if (czy_podniesiona_plytka == 1)
		{
			gracz->stojak->obraz_plytki[podniesiona_plytka.numer_plytki].setPosition(Vector2f(podniesiona_plytka.wspolrzedne));
			for (int i = 0; i < 7; i++) if (gracz->stojak->obraz_plytki[i].getGlobalBounds().contains(pozycja_mysz) && gracz->stojak->plytka[i].znak != NULL)
			{
				mieszanie_stojaka(podniesiona_plytka.numer_plytki, i);
			}
			for (int i = 2; i < 17; i++) for (int j = 2; j < 17; j++) if (plansza->pole[i][j].obraz.getGlobalBounds().contains(pozycja_mysz))
			{
				if (plansza->pole[i][j].stan == 0)
				{
					plansza->pole[i][j].tekstura = gracz->stojak->tekstury[podniesiona_plytka.numer_plytki];
					plansza->pole[i][j].obraz.setTexture(plansza->pole[i][j].tekstura);
					gracz->stojak->obraz_plytki[podniesiona_plytka.numer_plytki].setTexture(pusta_tekstura);
					plansza->pole[i][j].plytka = gracz->stojak->plytka[podniesiona_plytka.numer_plytki];
					gracz->stojak->plytka[podniesiona_plytka.numer_plytki].znak = NULL;
					plansza->pole[i][j].stan = 1;
					plansza->pole[i][j].zrodlo_plytki = podniesiona_plytka.numer_plytki;
				}
			}
			czy_podniesiona_plytka = 0;
		}

		if (ok->obraz.getGlobalBounds().contains(pozycja_mysz) && ok->aktywny == 1)
		{
			koniec_ruchu();
			ok->faza = 1;
		}
	}

	else
	{
		int poz_x = tablica_blanka.getPosition().x;
		int poz_y = tablica_blanka.getPosition().y + 26;
		for (int d = 0; d < 8; d++)  for (int e = 0; e < 4; e++)  if (pozycja_mysz.x > poz_x + d * 35 && pozycja_mysz.x < poz_x + (d + 1) * 35 && pozycja_mysz.y > poz_y + e * 35 && pozycja_mysz.y < poz_y + (e + 1) * 35)
		{
			for (int f = 2; f < 17; f++)  for (int g = 2; g < 17; g++)  if (plansza->pole[f][g].plytka.znak == 63)
			{
				plansza->pole[f][g].plytka.znak = wszystkie->plytki[d + 8 * e].znak;
				plansza->pole[f][g].tekstura = wszystkie->tekstury[d + 8 * e];
				plansza->pole[f][g].obraz.setTexture(plansza->pole[f][g].tekstura);
				plansza->pole[f][g].obraz.setColor(Color(120,120,120));
				f = 17;
				g = 17;
			}
			zdefiniuj_blanka = 0;
			koniec_ruchu();
		}
	}
}

void RozgrywkaZAI::petla_glowna()
{
	while (gra_trwa == 1)
	{
		pozycja_myszy = Mouse::getPosition();

		if (czy_podniesiona_plytka == 1) gracz->stojak->obraz_plytki[podniesiona_plytka.numer_plytki].setPosition(pozycja_myszy.x - podniesiona_plytka.bufor_kursora.x, pozycja_myszy.y - podniesiona_plytka.bufor_kursora.y);

		if (ruch_gracza == 0 && ok->faza == 0)
		{
			for (int i = 2; i < 17; i++) for (int j = 2; j < 17; j++) if (plansza->pole[i][j].stan != 0) komputer->pierwszy_ruch = 0;
			int wynik_przed_ruchem = komputer->wynik;
			komputer->szukaj();

			Wyniki *wskaznik_do_wynikow = tablica_wynikow;
			while (wskaznik_do_wynikow->kolejny_wynik != nullptr)  wskaznik_do_wynikow = wskaznik_do_wynikow->kolejny_wynik;
			wskaznik_do_wynikow->kolejny_wynik = new Wyniki(okno->getSize().y, numer_ruchu, to_string(komputer->wynik - wynik_przed_ruchem), to_string(komputer->wynik));

			komputer->stojak->losuj(worek);

			if (komputer->stojak->plytka[0].znak == NULL) koniec_gry(0);
			ruch_gracza = 1;
			numer_ruchu++;
		}

		while (okno->pollEvent(akcja))
		{
			if (akcja.type == Event::KeyPressed && akcja.key.code == Keyboard::Escape) gra_trwa = 0;

			if (akcja.type == Event::MouseButtonPressed && akcja.mouseButton.button == Mouse::Left) obsluga_myszy();
		}

		if (czy_poprawnie_lezy()) ok->aktywny = 1;
		else ok->aktywny = 0;
		ok->uaktywnij(ruch_gracza);
		ok->ruch_wciskania();

		okno->clear();
		okno->draw(plansza->obraz);
		for (int i = 2; i < 17; i++) for (int j = 2; j < 17; j++) okno->draw(plansza->pole[i][j].obraz);
		okno->draw(gracz->stojak->obraz);
		for (int i = 0; i < 7; i++) okno->draw(gracz->stojak->obraz_plytki[i]);
		okno->draw(ok->obraz);     	//plytki komputera  for (int i = 0; i < 7; i++) okno->draw(komputer->stojak->obraz_plytki[i]);
		Wyniki *wskaznik_do_wynikow = tablica_wynikow;
		while(wskaznik_do_wynikow != nullptr)
		{
			for (int j = 0; j <= 1; j++) okno->draw(wskaznik_do_wynikow->pola_tekstowe[j]);
			wskaznik_do_wynikow = wskaznik_do_wynikow->kolejny_wynik;
		}
		if (zdefiniuj_blanka == 1) okno->draw(tablica_blanka);
		okno->display();
	}
}