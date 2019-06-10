#pragma once
#include "Scene.h"
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

class PlayScene : public Scene {

	DWORD showTime;
	DWORD showTimeRate;

	GameMap *map;
	Camera *camera;
	Player *player;
	Unit*unit;
	Grid*grid;
	Scoreboard *sb;
	Score *score;
public:
	PlayScene();
	virtual ~PlayScene();
	virtual void Render();
	virtual void ProcessInput();
	virtual void Update(double dt);
	void CheckCollision(double dt = 0.0167f);
	//void CheckActive();
	void CheckCamera();
	//Player*GetPlayer();//hien tai, dung de truyen cho map roi truyen cho grid de xac dinh chiue di cua ninja va active cac unit theo chieu di
	void Reset();
	
};