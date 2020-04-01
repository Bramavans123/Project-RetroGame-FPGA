#include "../hdr/Candy.h"
#include "stdio.h"
#include "stdlib.h"

Candy::Candy()
{

}

Candy::~Candy()
{

}

void Candy::spawn(int width, int height)
{
	setPos(rand()%width + 1, rand()%height + 1);
}
