#pragma once
#include "../hdr/entity.h"

class Enemy : public entity
{
public:
	Enemy();
	~Enemy();

public:
	void draw() override;
};

