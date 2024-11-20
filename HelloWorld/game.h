#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include <fstream>
#include <vector>
#include "Play.h"
#include "constants.h"
#include "Paddle.h"

void SpawnBall();
void SetupScene();
void StepFrame(float elapsedTime);
void hud();
void loadfile();
void savefile();
void incrementsize();