#pragma once

class entity
{
public:
	entity();
	~entity();

public:

	virtual void setId(int id);
	virtual int getId() const;
	virtual void setPos(int x, int y);
	virtual void setX(int x);
	virtual int getX() const;
	virtual void setY(int y);
	virtual int getY() const;
	virtual void setSize(int size);
	virtual int getSize() const;

	virtual void draw() = 0;


private:
	int id;
	int x, y;
	int size;

};

