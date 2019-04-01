#include "Gra.h"


Gra::Gra()
{
	RenderWindow okno(VideoMode(530, 230), "oo", Style::Fullscreen);

	ZbiorPlytek wszystkie;

	Slownik slownik;

	Event akcja;

	tekstura_loga.loadFromFile("logo.png");
	logo.setTexture(tekstura_loga);
	logo.setPosition((okno.getSize().x - 472) / 2, 150);

	while (okno.isOpen())
	{
		while (okno.pollEvent(akcja))
		{
			if (akcja.type == Event::KeyPressed && akcja.key.code == Keyboard::Escape) okno.close();


			if (akcja.type == Event::KeyPressed && akcja.key.code == Keyboard::Space) RozgrywkaZAI(&okno, &wszystkie, &slownik);
		}



		okno.clear(Color(30, 100, 10));
		okno.draw(logo);

		okno.display();
	}
}

Gra::~Gra()
{
}