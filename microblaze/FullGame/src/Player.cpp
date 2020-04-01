#include "../hdr/Player.h"

Player::Player()
{
	score = 0;
}

Player::~Player()
{

}

int Player::getScore() const
{
	return score;
}

void Player::addScore(int score)
{
	this->score += score;
}

void Player::setRespawn(int x, int y)
{
	xres = x;
	yres = y;
}

void Player::respawn()
{
	setPos(xres, yres);
}

void Player::draw()
{

}

