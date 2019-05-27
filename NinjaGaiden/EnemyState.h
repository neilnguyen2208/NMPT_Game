#pragma once
#include "Entity.h"
#include "Animation.h"
#include "EnemyData.h"
#include "CollisionDetector.h"
#include "GameConfig.h"

class EnemyState {
public:
	enum State {
		Follow,
		Attack,
		Beaten
	};
	EnemyState(EnemyData *data);
	EnemyState();
	~EnemyState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual void ResetState();
protected:
	Animation *m_Animation;
	EnemyData *enemyData;
};
