#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EnemyWeaponData.h"
#include "GameConfig.h"

class EnemyWeaponState {
public:
	enum State {
		Follow,
		Defeated
	};
	EnemyWeaponState(EnemyWeaponData *data);
	EnemyWeaponState();
	~EnemyWeaponState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual void ResetState();
protected:
	Animation *m_Animation;
	EnemyWeaponData *enemyWeaponData;
};
