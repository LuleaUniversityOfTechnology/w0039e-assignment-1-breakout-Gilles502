#pragma once
#include "game.h"

struct Paddle {

	int tlx; //top left x
	int tly; //top left y
	int brx; //bottom right x
	int bry; //bottom left x

};

void DrawPaddle(Paddle& paddle);
void updatePaddle(Paddle& paddle);
bool IsColliding(Paddle& paddle, Play::GameObject& obj);
float max(float x, float y);
float min(float x, float y);