#pragma once
#include "Enemy.h"
#include "Textures.h"
#include "Animation.h"
#include "CatFollowState.h"

class Cat : public Enemy {
public:
	Cat();
	~Cat();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetState(EnemyState::State);
	virtual BoxCollider GetCollider();
	virtual void Spawn();
protected:
	EnemyState *catFollowState;
};