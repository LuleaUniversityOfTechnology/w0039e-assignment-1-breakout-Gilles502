#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"

void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 60 }, 4, "ball");
}

void StepFrame(float elapsedTime) {

	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	
	for (int i = 0; i < ballIds.size(); i++) {
		GameObject& Ball(Play::GetGameObject(ballIds[i]));
		Play::DrawObject(Ball);
		
	}
}