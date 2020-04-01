#pragma once
#include "entity.h"

class Player : public entity
{
public:
	Player();
	~Player();

public:
	int getScore() const;
	void addScore(int score);

	void setRespawn(int x, int y);
	void respawn();

	void draw() override;

private:
	int score;
	int xres, yres;

};

