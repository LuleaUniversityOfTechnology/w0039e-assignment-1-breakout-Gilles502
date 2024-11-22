#include "Paddle.h"
#include "Play.h"


void DrawPaddle(Paddle& paddle) {
	Play::Point2D topLeft = Play::Point2D(paddle.tlx, paddle.tly);
	Play::Point2D bottomRight = Play::Point2D(paddle.brx, paddle.bry);
	Play::DrawRect(topLeft, bottomRight, Play::cRed, true);
}
void updatePaddle(Paddle& paddle) {
	if (Play::KeyDown(Play::KeyboardButton(VK_LEFT))) { //if the player press the left arrow key it move the paddle on the x-axis 
		paddle.brx -= 5; 
		paddle.tlx -= 5;
	}
	if (Play::KeyDown(Play::KeyboardButton(VK_RIGHT))) {//if the player press the right arrow key it move the paddle on the x-axis
		paddle.brx += 5;
		paddle.tlx += 5;
	}
}
bool IsColliding(Paddle& paddle, Play::GameObject& obj) {
	Play::Point2D topLeft = Play::Point2D(paddle.tlx, paddle.tly);
	Play::Point2D bottomRight = Play::Point2D(paddle.brx, paddle.bry);
	const float dx = obj.pos.x - max(topLeft.x, min(obj.pos.x, bottomRight.x));
	const float dy = obj.pos.y - max(topLeft.y, min(obj.pos.y, bottomRight.y));
	return (dx * dx + dy * dy) < (obj.radius * obj.radius);
}
float max(float x, float y)
{
	return x > y ? x : y;
}

float min(float x, float y)
{
	return x < y ? x : y;
}