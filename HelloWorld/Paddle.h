#pragma once
#include "game.h"

struct Paddle {

	int tlx;
	int tly;
	int brx;
	int bry;

};

void DrawPaddle(Paddle& paddle);
void updatePaddle(Paddle& paddle);
bool IsColliding(Paddle& paddle, Play::GameObject& obj);
float max(float x, float y);
float min(float x, float y);