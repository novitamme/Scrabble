#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "Gra.h"

using namespace std;
using namespace sf;

int kolejkagracza = 0;
//////////////////////////  literki  ///////////////////////////

struct plytka
{
	char znak;
	int wartosc;
};

plytka jedna[33], worek[100], stojak[2][7];
int aktilosc[2], stanwora=100;

void okresl_plytki()
{
	jedna[0].znak = 97;//a
	jedna[1].znak = 88;//¹
	jedna[2].znak = 98;//b
	jedna[3].znak = 99;//c
	jedna[4].znak = 95;//æ
	jedna[5].znak = 100;//d
	jedna[6].znak = 101;//e
	jedna[7].znak = 89;//ê
	jedna[8].znak = 102;//f
	jedna[9].znak = 103;//g
	jedna[10].znak = 104;//h
	jedna[11].znak = 105;//i
	jedna[12].znak = 106;//j
	jedna[13].znak = 107;//k
	jedna[14].znak = 108;//l
	jedna[15].znak = 94;//³
	jedna[16].znak = 109;//m
	jedna[17].znak = 110;//n
	jedna[18].znak = 90;//ñ
	jedna[19].znak = 111;//o
	jedna[20].znak = 92;//ó
	jedna[21].znak = 112;//p
	jedna[22].znak = 114;//r
	jedna[23].znak = 115;//s
	jedna[24].znak = 96;//œ
	jedna[25].znak = 116;//t
	jedna[26].znak = 117;//u
	jedna[27].znak = 119;//w
	jedna[28].znak = 121;//y
	jedna[29].znak = 122;//z
	jedna[30].znak = 91;//Ÿ
	jedna[31].znak = 93;//¿
	jedna[32].znak = 63;//?
}

void okresl_wartosc()
{
	jedna[0].wartosc = 1;
	jedna[1].wartosc = 5;
	jedna[2].wartosc = 3;
	jedna[3].wartosc = 2;
	jedna[4].wartosc = 6;
	jedna[5].wartosc = 2;
	jedna[6].wartosc = 1;
	jedna[7].wartosc = 5;
	jedna[8].wartosc = 5;
	jedna[9].wartosc = 3;
	jedna[10].wartosc = 3;
	jedna[11].wartosc = 1;
	jedna[12].wartosc = 3;
	jedna[13].wartosc = 2;
	jedna[14].wartosc = 2;
	jedna[15].wartosc = 3;
	jedna[16].wartosc = 2;
	jedna[17].wartosc = 1;
	jedna[18].wartosc = 7;
	jedna[19].wartosc = 1;
	jedna[20].wartosc = 5;
	jedna[21].wartosc = 2;
	jedna[22].wartosc = 1;
	jedna[23].wartosc = 1;
	jedna[24].wartosc = 5;
	jedna[25].wartosc = 2;
	jedna[26].wartosc = 3;
	jedna[27].wartosc = 1;
	jedna[28].wartosc = 2;
	jedna[29].wartosc = 1;
	jedna[30].wartosc = 9;
	jedna[31].wartosc = 5;
	jedna[32].wartosc = 0;
}

void do_wora()
{
	aktilosc[0]=7;
	aktilosc[1]=7;

	fstream wyst;
	char wart[1];
	int ilosc;
	int q=0;
	wyst.open("wystap.txt", ios_base::in);
	for(int h=0; h<33; h++)
	{
		wyst.read(wart, 1);
		ilosc = wart[0] - 96;
		for(int b=0; b<ilosc; b++)
		{
			worek[q] = jedna[h];
			q++;
		}
	}
}

void losuj()
{
	int random=0;
	for(int c=0; c<7; c++)
	{
		if(stojak[kolejkagracza][c].znak == NULL)
		{
			if(stanwora>0)
			{
				random = (rand()%stanwora)+0;
				stojak[kolejkagracza][c] = worek[random];
				for(int c=random; c<stanwora; c++)  worek[c] = worek[c+1];
				stanwora--;
			}
			else
			{
				for(int m=c+1; m<7; m++)
				{
					if(stojak[kolejkagracza][m].znak != NULL)
					{
						stojak[kolejkagracza][c] = stojak[kolejkagracza][m];
						stojak[kolejkagracza][m].znak = NULL;
						m=6;
					}
				}
			}
		}
		if(stojak[kolejkagracza][c].znak == NULL)
		{
			aktilosc[kolejkagracza] = c;
			c=6;
		}
		//cout<<stojak[kolejkagracza][c].znak;
	}
}

///////////////////////////  plansza  ////////////////////////////

struct plansza
{
	plytka lezy;
	int premia; 
};

plansza pole[19][19];

void konwersja(int kierunek)
{
	plansza odwrotna [19][19];

	if(kierunek == 0)  for(int y=0; y<19; y++)  for(int x=0; x<19; x++)  odwrotna[x][y] = pole[y][x];
	
	else  for(int y=18; y>=0; y--)  for(int x=0; x<19; x++)  odwrotna[x][y] = pole[y][x];

	for(int y=0; y<19; y++)  for(int x=0; x<19; x++)  pole[x][y] = odwrotna[x][y];

	delete odwrotna;
}

void nadaj_wart()
{
	for(int y=0; y<19; y++)
	{
		for(int x=0; x<19; x++)
		{
			pole[x][y].lezy.znak = 30; 
			pole[x][y].premia = 0;
		}
	}

	for(int y=2; y<17; y++)
	{
		for(int x=2; x<17; x++)
		{
			pole[x][y].lezy.znak = 32; 
			pole[x][y].lezy.wartosc = 0;
		}
	}

	fstream prem;
	char wart[1];
	prem.open("premie.txt", ios_base::in);
	
	for(int y=2; y<17; y++)
	{
		for(int x=2; x<17; x++)
		{
			prem.read(wart, 1);
			pole[x][y].premia = wart[0] - 96;
		}
		prem.seekg(2,ios_base::cur);
	}
}

/////////////////////////// drzewo ////////////////////////////

struct wezel
{
	wezel* galaz[32];
	bool czy;
};

wezel pien;
wezel* wskaznik = &pien;

int numeracja(char litera)
{
	int liczba = 0; 
	if (litera < 113) liczba = litera - 88;
	if (litera > 113 && litera < 118) liczba = litera - 89;
	if (litera == 119) liczba = litera - 90;
	if (litera > 120) liczba = litera - 91;
	return liczba;
};

void drzewo(wezel* pobrany)
{
	fstream plik;
	char lit[1];
	int numer;
	wezel* aktualny = pobrany;
	aktualny -> czy = 0;
	plik.open("bazakrotka.txt", ios::in);

	while(plik.eof() != 1)
	{
		plik.read(lit,1);
		while(lit[0] != 10)
		{
			numer = numeracja(lit[0]);
			if(aktualny -> galaz[numer] == nullptr)
			{
				aktualny -> galaz[numer] = new wezel;
				aktualny = aktualny -> galaz[numer];
				for(int k=0; k<32; k++)
				{
					aktualny -> galaz[k] = nullptr;
				}
				aktualny -> czy = 0;
			}
			else aktualny = aktualny -> galaz[numer];
			plik.read(lit,1);
		}
		aktualny -> czy = 1;
		aktualny = pobrany;
	}
}

bool sprawdz(wezel* pobrany, plytka slowo[])
{
	wezel* aktualny = pobrany;
	int numer,  o=0;
	bool zly=0;
	char slowo1[10];
	for(int g=0; g<10; g++) slowo1[g] = slowo[g].znak;

	while (slowo1[o] != NULL)
	{
		numer = numeracja(slowo1[o]);
		if(aktualny -> galaz[numer] == nullptr)
		{
			slowo1[o+1] = NULL;
			zly = 1;
		}
		else
		{
			aktualny = aktualny -> galaz[numer];
			zly = 0;
		}
		o++;
	}
	if(aktualny -> czy == 1 && zly == 0) return 1;
	else return 0;
}

////////////////////////// konsola ////////////////////////////

HANDLE kolor;

void wyswietl()
{
	kolor = GetStdHandle( STD_OUTPUT_HANDLE );
	for(int y=0; y<19; y++)
	{
		for(int x=0; x<19; x++)
		{
			if (pole[x][y].lezy.znak != 32 && pole[x][y].lezy.znak != 30)   SetConsoleTextAttribute( kolor, 240);
			else if (pole[x][y].lezy.znak == 30)   SetConsoleTextAttribute( kolor, 15);
			else
			{
				if (pole[x][y].premia == 2) SetConsoleTextAttribute( kolor, 186 );
				else if (pole[x][y].premia == 3) SetConsoleTextAttribute( kolor, BACKGROUND_BLUE | BACKGROUND_INTENSITY );
				else if (pole[x][y].premia == 4) SetConsoleTextAttribute( kolor, 208 );
				else if (pole[x][y].premia == 5) SetConsoleTextAttribute( kolor, BACKGROUND_RED | BACKGROUND_INTENSITY );
				else 	SetConsoleTextAttribute( kolor, BACKGROUND_GREEN );
			}
			cout<<pole[x][y].lezy.znak;
		}
		cout<<endl;
	}
}

//////////////////////// szukaj slow //////////////////////////

struct najlepszy
{
	plytka plytki[10];
	int wyszly[7];
	bool orientacja; 
	int poczatek;
	int poziom;
	int punkty;
};

najlepszy jeden;
bool orient;
int czypoczatek=1;
int sumapkt=0;

int pierwsza_ostatnia (int x, int y, int min, int dziura)
{
int cel = 0;

for (int e=0; e<aktilosc[kolejkagracza]; e++)
	{
		if ((pole[x+2*min][y].lezy.znak!=32 && x!=dziura) || (pole[x+1*min][y-1].lezy.znak!=32 && y!=2) || (pole[x+1*min][y+1].lezy.znak!=32 && y!=16)) e=6;
		else x = x + min;
	}
cel=x;
return cel;
}

void poloz()
{
	int d = 0;
	while(jeden.plytki[d].znak != NULL)
	{
		if (jeden.orientacja == 0)		
		{	
			pole[jeden.poczatek+d][jeden.poziom].lezy = jeden.plytki[d];
			pole[jeden.poczatek+d][jeden.poziom].premia = 1;
		}
		else					
		{
			pole[jeden.poziom][jeden.poczatek+d].lezy = jeden.plytki[d];
			pole[jeden.poziom][jeden.poczatek+d].premia = 1;
		}
		d++;
	}
	for (int g=0; g<d-1+czypoczatek; g++)			stojak[kolejkagracza][jeden.wyszly[g]].znak = NULL;
	sumapkt = sumapkt + jeden.punkty;
	for(int y=0; y<10; y++) cout<<jeden.plytki[y].znak;
	cout<<endl<<"Punkty:  "<<jeden.punkty<<"           Suma:"<<sumapkt<<endl<<endl;
}

int podlicz(plytka akt[], int y, int p, int k)
{
	int suma=0,  e=0,  mnoznik=1;

	for(int v=p; v<=k; v++)
	{
		if(pole[v][y].premia <=3) suma = suma + akt[e].wartosc * pole[v][y].premia;
		if(pole[v][y].premia == 4) 
		{
			suma = suma + akt[e].wartosc;
			mnoznik = mnoznik*2;
		}
		if(pole[v][y].premia == 5) 
		{
			suma = suma + akt[e].wartosc;
			mnoznik = mnoznik*3;
		}
		//if(kolejkagracza==1) cout<<akt[e].wartosc<<" "<<pole[v][y].premia<<" "<<mnoznik<<" "<<suma<<"     "<<endl;
		e++;
	}
	suma = suma * mnoznik;
	if(kolejkagracza==0)  if(e == 8-czypoczatek) suma = suma + 50;
	return suma;
}

void kombinacja(int x, int y, int p, int k)
{
	int zbior[7]={0,1,2,3,4,5,6};
	plytka akt[10];
	bool koncz=0;
	int b=0;
	do
	{
		do
		{
			int blank1 = 1;
			int blanco1 = 0;
			int blank2 = 1;
			int blanco2 = 0;
			b=0;
			for(int q=0; q<=k-p; q++)
			{
				if(q == x-p)  akt[q] = pole[x][y].lezy;
				else 
				{
					akt[q] = stojak[kolejkagracza][zbior[b]];
					b++;
				}
				if (akt[q].znak == 63 && blank1 == 32) 
				{
					blanco2 = q;
					blank2 = 32;
				}
				if (akt[q].znak == 63 && blank2 == 1) 
				{
					blanco1 = q;
					blank1 = 32;
				}
			}
			akt[k-p+1].znak = NULL;
			akt[k-p+1].wartosc = NULL;
////////////////////////////////////////////////////////////////////////////////
			for(int r=0; r<blank2; r++)
			{
				if (blank2 == 32)	akt[blanco2].znak = jedna[r].znak;
				for(int h=0; h<blank1; h++)
				{
					if (blank1 == 32)	akt[blanco1].znak = jedna[h].znak;
					if(sprawdz(wskaznik, akt) == 1) 
					{
						if (podlicz(akt, y, p, k) > jeden.punkty) 
						{
							for(int d=0; d<=k-p; d++)	jeden.plytki[d] = akt[d];
							for(int r=0; r<k-p+czypoczatek; r++)	jeden.wyszly[r] = zbior[r];
							jeden.wyszly[k-p+czypoczatek] = NULL;
							jeden.plytki[k-p+1].znak = NULL;
							jeden.punkty = podlicz(akt, y, p, k);
							jeden.poczatek = p;
							jeden.poziom = y;
							jeden.orientacja = orient;
						}
					}
				}
			}

		}while  (next_permutation(zbior,zbior+k-p+czypoczatek));

//////////////////////////////////kombinacja////////////////////////////////////
		if(zbior[0]==aktilosc[kolejkagracza]-k+p-czypoczatek) koncz = 1;	

		for(int a=k-p+czypoczatek; a>0; a--)
		{
			if (zbior[a-1] != (a-k+p+aktilosc[kolejkagracza]-1-czypoczatek)) 
			{
				zbior[a-1] = zbior[a-1] + 1; 
				a=1;
			}
			else
			{
				int t=1;
				for(int s=a; s<=k-p+czypoczatek; s++)
				{
					zbior[s-1] = zbior[s-2] +1+t;
					t=0;
				}
			}
		}
//////////////////////////////////kombinacja////////////////////////////////////
	}while(koncz==0);
}

void stopien1(int x, int y)
{
	int poczatek=0,  koniec=0,  dlugosc=0,  zajete=0;

	if( (pole[x-1][y].lezy.znak == 32 || x == 2) && (pole[x+1][y].lezy.znak == 32 || x == 16) )
	{	
		poczatek = pierwsza_ostatnia(x,y,-1,3);
		koniec = pierwsza_ostatnia(x,y,1,15);

		for(int p=poczatek; p<=x; p++)
		{
			for(int k=x; k<=koniec; k++)
			{
				if(k-p>0 && k-p<=aktilosc[kolejkagracza])
				{
					kombinacja(x, y, p, k);
				}
			}
		}
	}
}

void szukaj()
{
	jeden.punkty = 0;
	for(int m=0; m<=1; m++)
	{
		orient = m;
		if (czypoczatek == 1)
		{
			int x=100;
			int y=9;
			for(int p=3; p<=9; p++)
			{
				for(int k=9; k<=15; k++)
				{
					if(k-p>1 && k-p<7)
					{
						kombinacja(x, y, p, k);
					}
				}
			}
		}
		else
		{
			for (int y=2; y<17; y++)
			{
				for (int x=2; x<17; x++)
				{
					if(pole[x][y].lezy.znak != 32)
					{
					stopien1(x,y);
					}
				}
			}
		}
	konwersja(m);
	}
	poloz();
	czypoczatek = 0;
}


/////////////////////////////////////////////SFML SFML SFML SFML/////////////////////////////////////////////////////////////////
Vector2i poz; 
int wyborblanka = 0;

void tekstury(Texture litera[33], Texture &board, Texture &doblanka ,Texture &ok, RectangleShape &plansza, RectangleShape &stojka, RectangleShape &OK, RectangleShape polesf[15][15], int lezacy[15][15], int wyjety[7], Sprite pionek[7], RectangleShape &blanek, Text wyniki[4][25], Font &font)
{
	font.loadFromFile("sansation.ttf");

	wyniki[0][0].setString("Ja                 Mariusz");
	for(int b=0; b<4; b++)  for(int c=0; c<25; c++)
	{
		wyniki[b][c].setFont(font); 
		wyniki[b][c].setCharacterSize(20); 
		wyniki[b][c].setColor(Color::White);
	}
	wyniki[0][0].setPosition(1050, 320);
	wyniki[1][0].setPosition(1050, 80);
	wyniki[2][0].setPosition(1150, 80);
	wyniki[3][0].setPosition(780, 265);

	for(int n=1; n<25; n++)
	{
		wyniki[0][n].setPosition(1040, 320+24*n);
		wyniki[1][n].setPosition(1090, 320+24*n);
		wyniki[2][n].setPosition(1160, 320+24*n);
		wyniki[3][n].setPosition(1210, 320+24*n);
	}

	for(int s=0; s<7; s++)  
	{
		pionek[s].setPosition (895+s*48, 172);
		wyjety[s] = 0;
	}

	for(int f=0; f<15; f++)  for(int g=0; g<15; g++)
	{
		polesf[f][g].setSize(Vector2f(46, 46));
		polesf[f][g].setPosition(f*48+21,g*48+21);
		polesf[f][g].setFillColor(Color::Transparent);
	}

	OK.setSize(Vector2f(150, 50));
	OK.setFillColor(Color(120,120,120));
	OK.setPosition( 800, 400);

	blanek.setSize(Vector2f(280, 166));
	blanek.setPosition( 800, 400);

	stojka.setSize(Vector2f(360, 70));
	stojka.setFillColor( Color (25, 105, 0 ));
	stojka.setPosition( 882, 160 );

	plansza.setSize(Vector2f(720, 720));
	plansza.setPosition( 20, 20 ); 

	ok.loadFromFile( "ok.jpg" );

	board.loadFromFile( "plansza.jpg" );

	doblanka.loadFromFile( "blank.jpg" );

	litera[0].loadFromFile( "literaa.jpg" );
    litera[1].loadFromFile( "literaom.jpg" );
	litera[2].loadFromFile( "literab.jpg" );
	litera[3].loadFromFile( "literac.jpg" );
	litera[4].loadFromFile( "literaci.jpg" );
	litera[5].loadFromFile( "literad.jpg" );
	litera[6].loadFromFile( "literae.jpg" );
	litera[7].loadFromFile( "literaem.jpg" );
    litera[8].loadFromFile( "literaf.jpg" );
	litera[9].loadFromFile( "literag.jpg" );
	litera[10].loadFromFile( "literah.jpg" );
	litera[11].loadFromFile( "literai.jpg" );
	litera[12].loadFromFile( "literaj.jpg" );
	litera[13].loadFromFile( "literak.jpg" );
	litera[14].loadFromFile( "literal.jpg" );
	litera[15].loadFromFile( "literaeu.jpg" );
    litera[16].loadFromFile( "literam.jpg" );
	litera[17].loadFromFile( "literan.jpg" );
	litera[18].loadFromFile( "literani.jpg" );
	litera[19].loadFromFile( "literao.jpg" );
	litera[20].loadFromFile( "literaou.jpg" );
	litera[21].loadFromFile( "literap.jpg" );
	litera[22].loadFromFile( "literar.jpg" );
	litera[23].loadFromFile( "literas.jpg" );
	litera[24].loadFromFile( "literasi.jpg" );
	litera[25].loadFromFile( "literat.jpg" );
    litera[26].loadFromFile( "literau.jpg" );
	litera[27].loadFromFile( "literaw.jpg" );
	litera[28].loadFromFile( "literay.jpg" );
	litera[29].loadFromFile( "literaz.jpg" );
	litera[30].loadFromFile( "literazi.jpg" );
	litera[31].loadFromFile( "literarz.jpg" );
	litera[32].loadFromFile( "literabl.jpg" );
}

bool krzywo(int lezacy[15][15], int ktory)
{
	int  ef=0,  gie=0,  pion=0,  krzywo=0,  numerek=0,  styk=0;

	for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  if(lezacy[f][g]==1)
	{
		if( lezacy[f-1][g]==2  ||  lezacy[f+1][g]==2  ||  (lezacy[f][g-1]==2  &&  g!=0)  ||  (lezacy[f][g+1]==2  &&  g!=14) ) styk=1;
		if (numerek==0)
		{
			ef=f;
			gie=g;
		}
		if (numerek==1) 
		{
			if (f==ef) pion=1;
			else if (g==gie) pion=2;
		}
		if ((pion==1 && f!=ef) || (pion==2 && g!=gie) || (pion==0 && numerek!=0))  krzywo=1; 
		numerek++;
	}
	if (krzywo==0)  for(int q=0; q<ktory; q++)
	{
		if (lezacy[ef][gie]==0) krzywo=1;
		else if (lezacy[ef][gie]==2) q--;
		if(pion==2) ef++;
		else if(pion==1) gie++;							
	}
	if(pion==2) ef--;
	else if(pion==1) gie--;
	if(czypoczatek==0 && styk==0) krzywo=1;
	if(czypoczatek==1 && lezacy[7][7]==0) krzywo=1;
	if(krzywo==1) return 1;
	else return 0;
}

void mieszanie(Sprite pionek[7], int xsiak, int ygrek, int &first, int &second)
{
	plytka zastep;
	if(poz.x >= 750 && poz.y < 390 && first != 8) pionek[first].setPosition (Vector2f ( poz.x-xsiak, poz.y-ygrek ));
	else
	{
		pionek[first].setPosition(895+first*48,172);
		first = 8;
	}

	if (second != 8) 	
	{
		pionek[first].setPosition(895+first*48, 172);
		int q = 1;
		if(first>second)	q=-1;
		zastep = stojak[1][first]; 
		for(int g=first; g*q<second*q; g=g+q)  stojak[1][g] = stojak[1][g+q];
		stojak[1][second] = zastep;
		first = 8;
		second = 8;
	}
}

void polozdejmij(int lezacy[15][15], int &ktory, int wyjety[7], int f, int g)
{
	if (lezacy[f][g]==0 && ktory<7 ) 
	{
		pole[f+2][g+2].lezy = stojak[1][ktory];
		lezacy[f][g]=1;

		stojak[1][ktory].znak = NULL;
		wyjety[ktory]=1;

		ktory++;
	}
	else if (lezacy[f][g]==1)
	{
		ktory--;

		if (pole[f+2][g+2].lezy.wartosc == 0)  pole[f+2][g+2].lezy.znak = 63;
		stojak[1][ktory] = pole[f+2][g+2].lezy;
		wyjety[ktory]=0;

		pole[f+2][g+2].lezy.znak = 32;
		lezacy[f][g]=0;
	}
}

void konwersjaSF(int kierunek, int lezacy[15][15])
{
	int odwrot [15][15];
	if(kierunek == 0)  for(int y=0; y<15; y++)  for(int x=0; x<15; x++)  odwrot[x][y] = lezacy[y][x];
	else  for(int y=14; y>=0; y--)  for(int x=0; x<15; x++)  odwrot[x][y] = lezacy[y][x];
	for(int y=0; y<15; y++)  for(int x=0; x<15; x++)  lezacy[x][y] = odwrot[x][y];
}

bool zatwierdz_slowo (int lezacy[15][15], RectangleShape polesf[15][15], int ktory, int &wynikgracza)
{
	int akcept=1, kolejny=0, f1=0;
	for(int p=0; p<=1; p++) 
	{
		for(int g=0; g<15; g++)  for(int f=0; f<15; f++)  if(lezacy[f][g]==1) 
		{
			plytka aktuel[15];
			f1=f;
			while(lezacy[f1-1][g]!=0 && f1!=0)  f1--;	
			f=f1;
			while(lezacy[f][g]!=0 && f!=15) 
			{
				aktuel[kolejny] = pole[f+2][g+2].lezy;
				kolejny++;
				f++;
			}
			f--;
			aktuel[kolejny].znak=NULL;	
			if(kolejny>1) 
			{
				if(sprawdz(wskaznik,aktuel)==0) 	akcept = 0;
				wynikgracza = wynikgracza + podlicz(aktuel, g+2, f1+2, f+2);
			}
			kolejny = 0;
		}
		konwersja(p);
		konwersjaSF(p, lezacy);
	}
	if(kolejkagracza==1)  if(ktory==7) wynikgracza = wynikgracza + 50;
	if(akcept==1)  return 1;
	else return 0;
}

void konczkolej(bool taknie, int lezacy[15][15], int &ktory, int wyjety[7])
{
	int kt = ktory;
	for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  if(lezacy[f][g]==1)
	{
		if(taknie==1)
		{	
			lezacy[f][g]=2;		
			for(int u=0; u<ktory; u++) stojak[1][u].znak = NULL;
			pole[f+2][g+2].premia = 1;
		}
		else 
		{
			kt--;
			if(pole[f+2][g+2].lezy.wartosc == 0) stojak[1][kt] = jedna[32];
			else stojak[1][kt] = pole[f+2][g+2].lezy;
			lezacy[f][g]=0;
			pole[f+2][g+2].lezy.znak = 32;
		}
	}
	for(int u=0; u<7; u++) wyjety[u]=0;
	ktory = 0;
}

void wyswietlanie(int wyjety[7], Sprite pionek[7], int lezacy[15][15], RectangleShape polesf[15][15], Texture litera[33])
{
	for(int f=0; f<aktilosc[1]; f++)   if(wyjety[f] == 0)
	{
		for(int j=0; j<33; j++)  if(stojak[1][f].znak == jedna[j].znak)  pionek[f].setTexture(litera[j]);
		pionek[f].setColor(Color::White);
	}
	else pionek[f].setColor(Color::Black);

	for(int f=0; f<15; f++)  for(int g=0; g<15; g++) 
	{
		if(lezacy[f][g]>0)
		{
			if (pole[f+2][g+2].lezy.wartosc == 0)  polesf[f][g].setFillColor(Color(120,120,120));
			else polesf[f][g].setFillColor(Color::White);
			for(int j=0; j<33; j++)  if(pole[f+2][g+2].lezy.znak == jedna[j].znak)  polesf[f][g].setTexture(&litera[j]);
		}
		else polesf[f][g].setFillColor(Color::Transparent);
	}
}

void rozpocznij(int lezacy[15][15], int &nrkolejki, int &sumagracza, int &ktozacz, Text wyniki[2][25], int &koniec, int wynikgracza)
{
	do_wora();
	nadaj_wart();
	for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  lezacy[f][g]=0;
	for(int j=0; j<2; j++)  for(int k=0; k<7; k++)  stojak[j][k].znak = NULL;
	czypoczatek=1;
	nrkolejki=1;
	sumagracza=0;
	sumapkt=0;
	stanwora=100;
	for(int y=0; y<2; y++) aktilosc[y]=7;
	kolejkagracza=0;
	losuj();
	kolejkagracza=1;
	losuj();
	kolejkagracza = (rand()%2)+0;
	ktozacz=kolejkagracza;
	for(int w=0; w<=3; w++) for(int r=1; r<=24; r++)
	{
		wyniki[w][r].setString(" ");
		wyniki[w][r].setColor(Color::White);
	}
	koniec=0;
	wyniki[3][0].setString(" ");
	wynikgracza=0;
}

void funkcja()
{
	RenderWindow okno( VideoMode( 1320, 620), "Gra", Style::Fullscreen);

	Texture litera[33], board, ok, doblanka;
	RectangleShape plansza,  stojka,  OK,  polesf[15][15], blanek;
	Sprite pionek[7];
	int  wyjety[7], lezacy[15][15],  ktory=0,  first = 8,  second = 8, xsiak = 0,  ygrek = 0, wynikgracza=0 ,sumagracza, nrkolejki, ktozacz, koniec=0;
	Font font;
	Text wyniki[4][25];

	tekstury(litera, board, doblanka, ok, plansza, stojka, OK, polesf, lezacy, wyjety, pionek, blanek, wyniki, font);
	plansza.setTexture( &board );
	OK.setTexture( &ok );
	blanek.setTexture( &doblanka );

	rozpocznij(lezacy, nrkolejki, sumagracza, ktozacz, wyniki, koniec, wynikgracza);

//petla glowna///////////////////////////////////////
    while( okno.isOpen() )
    {
		poz = Mouse::getPosition( okno );
		if(kolejkagracza==0)
		{
			szukaj();
			losuj();
			wyniki[2][0].setString(to_string(aktilosc[0]));
			for(int f=0; f<15; f++)  for(int g=0; g<15; g++) 
			{
				if(lezacy[f][g]!=0) czypoczatek=0;
				if(pole[f+2][g+2].lezy.znak != 32)	lezacy[f][g]=2;
			}
			wyniki[2][nrkolejki].setString(to_string(jeden.punkty));
			wyniki[3][nrkolejki].setString(to_string(sumapkt));
			if(ktozacz == 1) nrkolejki++; 
			kolejkagracza=1;
		}
//czy poprawne slowo//
		OK.setFillColor(Color::White);
		if (krzywo(lezacy, ktory) == 1) OK.setFillColor(Color(120,120,120));
//zdarzenie//
		Event klik;
		while( okno.pollEvent( klik ) )
        {
//wylacz/////
			if( klik.type == Event::KeyPressed && klik.key.code == Keyboard::Escape )	okno.close();
//od nowa////
			if( klik.type == Event::KeyPressed && klik.key.code == Keyboard::N)  rozpocznij(lezacy, nrkolejki, sumagracza, ktozacz, wyniki, koniec, wynikgracza);
//jak blank//
			if(koniec==0)
			{
				if(wyborblanka>0)  
				{
					for(int d=0; d<8; d++)  for(int e=0; e<4; e++)  if( klik.type == Event::MouseButtonPressed && klik.mouseButton.button == Mouse::Left && poz.x > 800+d*35  && poz.x < 835+d*35 && poz.y > 426+e*35 && poz.y < 461+e*35 )
					{
						for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  if(pole[f+2][g+2].lezy.znak == 63) 
						{
						pole[f+2][g+2].lezy.znak = jedna[d+8*e].znak;
						f=14;
						g=14;
						}
						wyborblanka--;
					}
				}
//podnies////
				else 
				{
					for(int s=0; s<aktilosc[1]; s++)  if(wyjety[s] == 0) 
					{
						if( klik.type == Event::MouseButtonPressed && klik.mouseButton.button == Mouse::Left && poz.x >= 895+s*48 && poz.x < 941+s*48 && poz.y >= 172 && poz.y < 218 && first==8) 
					    {
					 	    xsiak = poz.x-895-s*48;
							ygrek =	poz.y-172;	
							first = s;
						}
						else if( klik.type == Event::MouseButtonPressed && klik.mouseButton.button == Mouse::Left && poz.x >= 895+s*48 && poz.x < 941+s*48 && poz.y >= 172 && poz.y < 218 && first!=8) second = s; 		
					}
//polozdejm//
					for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  if( klik.type == Event::MouseButtonPressed && klik.mouseButton.button == Mouse::Left && poz.x > f*48+20 && poz.x < f*48+68 && poz.y > g*48+20 && poz.y < g*48+68 ) polozdejmij(lezacy, ktory, wyjety, f, g );
//zatwierdz//
					if( klik.type == Event::MouseButtonPressed && klik.mouseButton.button == Mouse::Left && poz.x>800 && poz.x<950 && poz.y>400 && poz.y<450 && krzywo(lezacy, ktory)==0)
					{
						for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  if(lezacy[f][g]==1 && pole[f+2][g+2].lezy.znak==63) wyborblanka++;
						if(wyborblanka==0)
						{
							if (zatwierdz_slowo(lezacy, polesf, ktory, wynikgracza) == 1)  konczkolej(1, lezacy, ktory, wyjety);
							else
							{
								konczkolej(0, lezacy, ktory, wyjety);
								wynikgracza=0;
							}
							sumagracza = sumagracza + wynikgracza;
							losuj();
							kolejkagracza=0;
							wyniki[0][nrkolejki].setString(to_string(wynikgracza));
							wyniki[1][nrkolejki].setString(to_string(sumagracza));
							wynikgracza=0;
							if(ktozacz == 0)nrkolejki++;
							for(int f=0; f<15; f++)  for(int g=0; g<15; g++) if(lezacy[f][g]!=0) czypoczatek=0;
						}
					}
				}
			}
		}
//koniec partii////////////////////////////////////////
		if(koniec==0 && ( aktilosc[0]==0 || aktilosc[1]==0 ) )
		{
			int a=0, mnoz=1, kto=1;
			if (aktilosc[1]==0)
			{
				mnoz=-1;  
				kto=0;
			}
			if(kolejkagracza != ktozacz) nrkolejki++;

			while(stojak[kto][a].znak != NULL)
			{
				wynikgracza = wynikgracza + stojak[kto][a].wartosc;
				a++;
			}
			kolejkagracza=2;
			koniec=1;
			sumagracza = sumagracza - (mnoz * wynikgracza);
			sumapkt = sumapkt + (mnoz * wynikgracza);
			for(int v=0; v<4; v++)  wyniki[v][nrkolejki].setColor(Color::Green);
			wyniki[0][nrkolejki].setString(to_string(wynikgracza * ( -mnoz) ) );
			wyniki[1][nrkolejki].setString(to_string(sumagracza) );
			wyniki[2][nrkolejki].setString(to_string(wynikgracza * mnoz) );
			wyniki[3][nrkolejki].setString(to_string(sumapkt) );

			if(sumagracza>sumapkt) wyniki[3][0].setString(L"Wygranko! Aby rozp¹cz¹æ now¹ grê, wciœnij 'N'.");
			else if(sumagracza==sumapkt) wyniki[3][0].setString(L"Noo, remisik! Aby rozp¹cz¹æ now¹ grê, wciœnij 'N'.");
			else if(sumagracza<sumapkt) wyniki[3][0].setString(L"Przegranko XD! Aby rozp¹cz¹æ now¹ grê, wciœnij 'N'.");
		}
//mieszanie stojaka////////////////////////////////////
		mieszanie(pionek, xsiak, ygrek, first, second);
//wyswietl/////////////////////////////////////////////
		wyniki[1][0].setString(to_string(stanwora));
		wyswietlanie(wyjety, pionek, lezacy, polesf, litera );
		okno.clear();
	    okno.draw(plansza);
		okno.draw(stojka);
		okno.draw(OK);
		for(int h=0; h<4; h++)  for(int f=0; f<=nrkolejki; f++)  okno.draw(wyniki[h][f]);
		if (wyborblanka>0) okno.draw(blanek);
		for(int k=0; k<aktilosc[1]; k++)		okno.draw(pionek[k]);
		for(int f=0; f<15; f++)  for(int g=0; g<15; g++)  okno.draw(polesf[f][g]);
		okno.display();
	}
}


int main()
{
	srand(time(NULL));
//	okresl_plytki();
//	okresl_wartosc();
//	for(int k=0; k<32; k++)	 wskaznik -> galaz[k] = nullptr;
//	drzewo(wskaznik);
//	funkcja();
	Gra gra;
	return 0;
}