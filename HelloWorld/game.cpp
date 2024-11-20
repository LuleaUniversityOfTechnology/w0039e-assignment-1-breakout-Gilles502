#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "game.h"
#include "Paddle.h"

Paddle p;
int s = 5;
int c = 0;
int* highScore = new int[s];
int score = 0;


void SpawnBall() {
	const int objectId = Play::CreateGameObject(ObjectType::TYPE_BALL, { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 200 }, 8, "ball");
	GameObject& ball = Play::GetGameObject(objectId);
	ball.velocity = normalize({ 1, -1 }) * ballSpeed;
}

void hud() {
	int space = 30;
	Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH / 10, DISPLAY_HEIGHT / 10), std::to_string(score).c_str());
	Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH - (DISPLAY_WIDTH / 12), DISPLAY_HEIGHT - (DISPLAY_HEIGHT /2)), "High Score:");
	for (int i = 0; i < 5; i++) {
		Play::DrawDebugText(Play::Point2D(DISPLAY_WIDTH - (DISPLAY_WIDTH / 12), DISPLAY_HEIGHT - (DISPLAY_HEIGHT / 2) - space), std::to_string(highScore[i]).c_str());
		space += 20;
	}
}
void savefile() {
	
	std::ofstream file("highscore.txt");
	if (file.is_open()) {
		for (int i = 0; i < s; i++) {
			file << highScore[i]<<"\n";
		}
		file.close();
	}
	else {
		std::cerr << "File error.\n";
	}
	delete[] highScore;
}
void loadfile() {
	for (int i = 0; i < s; ++i) {
		highScore[i] = 0;
	}
	std::ifstream file("highscore.txt");
	if (file.is_open()) {
		c = 0;
		std::string row;
		while (std::getline(file, row)) {
			if (row.empty()) {
				break;
			}
			if (c == s) {
				incrementsize();
			}
			int hs = std::stoi(row);
			highScore[c]=hs; 
			c++;
		}
		file.close();  
	}
	else {
		std::cerr << "File error.\n";
	}

}
void incrementsize() {
	s ++;
	int* hstemp = new int[s];
	for (int i = 0; i < c; i++) {
		hstemp[i] = highScore[i];
	}
	delete[] highScore;
	highScore = hstemp;
}

void SetupScene() {
	for (int x = 0; x < DISPLAY_WIDTH / 18; x++) { //I used the display width/18 as max number of brick in a row so it can fill every resolution you use
		for (int y = 1; y <= 8; y++){
			Play::CreateGameObject(ObjectType::TYPE_BRICK, { (x * 18) , DISPLAY_HEIGHT - (y * 12)}, 8, "brick");
		}
	}
	p.tlx = DISPLAY_WIDTH/2;//same as the number of brick,i used the display width so it scale with the resolution
	p.tly = 30;
	p.brx = (DISPLAY_WIDTH / 2)+(DISPLAY_WIDTH / 6);////same as the number of brick,i used the display width so it scale with the resolution
	p.bry = 45;

}

void StepFrame(float elapsedTime) {

	const std::vector<int> brickIds = Play::CollectGameObjectIDsByType(TYPE_BRICK);
	for (int i = 0; i < brickIds.size(); i++) {
		GameObject& brick = Play::GetGameObject(brickIds[i]);
		Play::UpdateGameObject(brick);
		Play::DrawObject(brick);
	}
	const std::vector<int> ballIds = Play::CollectGameObjectIDsByType(TYPE_BALL);
	for (int i = 0; i < ballIds.size(); i++) {
		GameObject& ball(Play::GetGameObject(ballIds[i]));
		for (int i = 0; i < brickIds.size(); i++) {
			GameObject& brick = Play::GetGameObject(brickIds[i]);
			if (Play::IsColliding(ball, brick)) { //collision with brick
				Play::DestroyGameObject(brickIds[i]);
				ball.velocity.y = -(ball.velocity.y);
				score++;

			}
		}

	}
	for (int i = 0; i < ballIds.size(); i++) {
		GameObject& ball(Play::GetGameObject(ballIds[i]));
		if (ball.pos.x >= (DISPLAY_WIDTH - ball.radius)) {
			ball.velocity.x = -(ball.velocity.x);//flip the direction of the ball
		}
		else if (ball.pos.x <= 0) {
			ball.velocity.x = -(ball.velocity.x);
		}
		else if (ball.pos.y >= DISPLAY_HEIGHT - ball.radius) {
			ball.velocity.y = -(ball.velocity.y);
		}
		else if (IsColliding(p, ball))//collision with paddle
		{
			int r = rand() % 6;
			ball.velocity.y = -(ball.velocity.y);
			ball.velocity.x = ball.velocity.x + r;
			std::cout << r;

		}
		else if (ball.pos.y <= 0) {
			int y = 0;
			for (y = 0; y < s; y++) {
				int hs = highScore[y];
				if (score > hs) {
					highScore[y] = score;
					score = hs;
				}
			}
			if (s == 0) {
				highScore[0] = score;
			}
			Play::DestroyGameObject(ballIds[i]);
			for (int i = 0; i < brickIds.size(); i++) {
				Play::DestroyGameObject(brickIds[i]);
			}
			score = 0;
			SetupScene();
			SpawnBall();
			break;
		}
		Play::UpdateGameObject(ball);
		Play::DrawObject(ball);

	}
	updatePaddle(p);
	DrawPaddle(p);
	hud();
}