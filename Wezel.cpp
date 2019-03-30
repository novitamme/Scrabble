#include "Wezel.h"


Wezel::Wezel()
{
	for (int k = 0; k < 32; k++)
	{
		galaz[k] = nullptr;
	}

	czy_istnieje = 0;
}

Wezel::~Wezel()
{
}
