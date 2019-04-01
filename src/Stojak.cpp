#include "Stojak.h"


Stojak::Stojak(Vector2u rozmiar_okna, bool czyj)
{
	stan = 7;

	if(czyj == 1) tekstura.loadFromFile("stojak.jpg");
	obraz.setPosition(rozmiar_okna.y + 100, czyj * 100);
	obraz.setTexture(tekstura);

	pusta_tekstura.loadFromFile("pusta.png");

	for (int i = 0; i < 7; i++)
	{
		obraz_plytki[i].setPosition(obraz.getPosition().x + 10 + 48 * i, obraz.getPosition().y + 13 );
		plytka[i].znak = NULL;
	}
}

Stojak::~Stojak()
{
}

void Stojak::losuj(Worek *worek)
{
	int random = 0;
	for (int c = 0; c < 7; c++)
	{
		if (plytka[c].znak == NULL)
		{
			if (worek->stan > 0)
			{
				random = (rand() % worek->stan) + 0;
				plytka[c] = worek->plytki[random];
				tekstury[c] = worek->tekstury[random];
				for (int c = random; c < worek->stan - 1; c++)  worek->plytki[c] = worek->plytki[c + 1];
				for (int c = random; c < worek->stan - 1; c++)  worek->tekstury[c] = worek->tekstury[c + 1];
				worek->stan--;
			}
			else
			{
				for (int m = c + 1; m < 7; m++)
				{
					if (plytka[m].znak != NULL)
					{
						plytka[c] = plytka[m];
						tekstury[c] = tekstury[m];
						plytka[m].znak = NULL;
						m = 6;
					}
				}
			}
		}
		obraz_plytki[c].setTexture(tekstury[c]);
		if (plytka[c].znak == NULL)
		{
			stan = c;
			for (int i = stan; i < 7; i++) obraz_plytki[i].setTexture(pusta_tekstura);
			c = 6;
		}
	}
}