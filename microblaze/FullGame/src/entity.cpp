#include "../hdr/entity.h"

entity::entity()
{

}

entity::~entity()
{

}

void entity::setId(int id)
{
	this->id = id;
}

int entity::getId() const
{
	return id;
}

void entity::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void entity::setX(int x)
{
	this->x = x;
}

int entity::getX() const
{
	return x;
}

void entity::setY(int y)
{
	this->y = y;
}

int entity::getY() const
{
	return y;
}

void entity::setSize(int size)
{
	this->size = size;
}

int entity::getSize() const
{
	return size;
}
