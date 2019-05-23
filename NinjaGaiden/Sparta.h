#pragma once
#include "Textures.h"
#include "Animation.h"
#include "GameConfig.h"
#include "Enemy.h"
#include "EnemyData.h"
#include "EnemyState.h"
#include "SpartaFollowState.h"

class Sparta : public Enemy {
public:
	Sparta();
	~Sparta();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	//virtual float GetWidth();
	//virtual float GetHeight();
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetState(EnemyState::State);
	virtual BoxCollider GetCollider();
	virtual void Spawn();
protected:
	EnemyState *spartaFollowState;
};