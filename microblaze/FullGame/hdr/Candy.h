#pragma once
#include "../hdr/entity.h"

class Candy : public entity
{
public:
	Candy();
	~Candy();

public:
	void spawn(int width, int height);

	void draw() override;

private:

};

