#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Textures.h"
#include"Enemy.h"
#include"EnemyWeapon.h"

class ThrowerBullet:public EnemyWeapon
{
public:

	ThrowerBullet();
	~ThrowerBullet();
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);
	virtual void Render();
	virtual void Update(double dt);
};

