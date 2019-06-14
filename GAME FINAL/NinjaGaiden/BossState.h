#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include"EnemyWeapon.h"
#include"BossBullet.h"
#include"Unit.h"
#include"Grid.h"
#include"CollisionDetector.h"
class BossState : public EnemyState {

	//First turn
	EnemyWeapon*bossBullet_1;
	EnemyWeapon*bossBullet_2;
	EnemyWeapon*bossBullet_3;

	Grid*grid;
	bool isJump;
	int turnMove;
	int sidePosition; //0 Right 1 Left
	bool isAttack;
	bool isHaveLand;

public:
	BossState(EnemyData *data);
	~BossState();
	virtual void ResetState();
	virtual void Update(double dt);
	virtual void OnCollision(Entity*impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void Render();
	Animation* jump_Animation;
	Animation* explode_Animation;
};