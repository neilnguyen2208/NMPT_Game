#pragma once
#include "Textures.h"
#include "GameMap.h"
#include "Entity.h"
#include "CollisionDetector.h"
#include "Player.h"
#include "Unit.h"
#include "Scoreboard.h"
#include "Graphic.h"
#include "Score.h"
#include "SoundManager.h"

class PlayScene {
private:
	GameMap *map;
	Grid*grid;
	Unit*unit;
	Player*player;
	Scoreboard *sb;
	Score *score;
	bool pause;
	int gameTime;
	double dtTime;
public:
	PlayScene();
	virtual ~PlayScene();
	virtual void Render();
	virtual void ProcessInput();
	virtual void Update(double dt);
	virtual void CheckCollision(double dt = 0.0167f);
	virtual void CheckCamera();
	virtual void Reset();
};