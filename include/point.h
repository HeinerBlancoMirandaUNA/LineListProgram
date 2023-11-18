#pragma once
#include "user_interaction.h"

class Point
{
public:
	Point();
	virtual ~Point();
	int x, y;
	bool isTouching(UserInteraction& User);
};

