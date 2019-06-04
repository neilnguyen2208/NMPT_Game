#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include "ThrowerBullet.h"
class ThrowerAttackState : public EnemyState {
public:
	ThrowerAttackState(EnemyData *data);
	~ThrowerAttackState();
	virtual void ResetState();
	virtual void Update(double dt);
private:
	ThrowerBullet *throwerBullet;
};