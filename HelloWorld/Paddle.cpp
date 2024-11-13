#include "Paddle.h"
#include "Play.h"


void DrawPaddle(Paddle& paddle) {
	Play::Point2D bottomLeft = Play::Point2D(paddle.tlx, paddle.tly);
	Play::Point2D topRight = Play::Point2D(paddle.brx, paddle.bry);
	Play::DrawRect(bottomLeft, topRight, Play::cRed, true);
}
void updatePaddle(Paddle& paddle) {
	if (Play::KeyDown(Play::KeyboardButton(VK_LEFT))) {
		paddle.brx -= 5;
		paddle.tlx -= 5;
	}
	if (Play::KeyDown(Play::KeyboardButton(VK_RIGHT))) {
		paddle.brx += 5;
		paddle.tlx += 5;
	}
}
bool IsColliding(Paddle& paddle, Play::GameObject& obj) {
	Play::Point2D bottomLeft = Play::Point2D(paddle.tlx, paddle.tly);
	Play::Point2D topRight = Play::Point2D(paddle.brx, paddle.bry);
	const float dx = obj.pos.x - max(bottomLeft.x, min(obj.pos.x, topRight.x));
	const float dy = obj.pos.y - max(bottomLeft.y, min(obj.pos.y, topRight.y));
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