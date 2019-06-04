#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Textures.h"
#include"Enemy.h"
#include"EnemyWeapon.h"
#include"EnemyWeaponState.h"
class ThrowerBullet :public EnemyWeapon
{
public:

	ThrowerBullet();
	~ThrowerBullet();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual BoxCollider GetCollider();
	virtual void Spawn();

private:
	EnemyWeaponState *enemyWeaponDestroyState;
};

