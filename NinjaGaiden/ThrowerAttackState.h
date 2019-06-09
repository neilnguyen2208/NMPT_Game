#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "ThrowerBullet.h"
#include "EnemyWeapon.h"
#include"Unit.h"
class ThrowerAttackState : public EnemyState {
public:
	ThrowerAttackState(EnemyData *data);
	~ThrowerAttackState();
	virtual void ResetState();
	virtual void Update(double dt);
	virtual void Render();
	virtual State GetState();
private:
	EnemyWeapon*throwerBullet;

	Grid* grid;
	Unit* unit;
};