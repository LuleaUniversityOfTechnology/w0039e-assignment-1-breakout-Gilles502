#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, 4, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

void StepFrame(float elapsedTime) {

	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++) {
		GameObject& ball(Play::GetGameObject(ballIds[i]));
		if (ball.pos.x >= (DISPLAY_WIDTH - ball.radius)) {
			ball.velocity.x = -(ball.velocity.x);
		}
		else if (ball.pos.x <= 0) {
			ball.velocity.x = -(ball.velocity.x);
		}
		else if (ball.pos.y <= 0) {
			ball.velocity.y = -(ball.velocity.y);
		}
		else if (ball.pos.y >= DISPLAY_HEIGHT - ball.radius) {
			ball.velocity.y = -(ball.velocity.y);
		}
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);
		
	}
}