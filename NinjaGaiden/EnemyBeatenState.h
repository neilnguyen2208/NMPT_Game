#pragma once
#include"Enemy.h"
#include"EnemyData.h"
#include"Animation.h"
#include"Textures.h"
#include"EnemyState.h"
#include"GameConfig.h"
#include"Grid.h"

class EnemyBeatenState:public EnemyState
{	
public:
	EnemyBeatenState(EnemyData *data);
	~EnemyBeatenState();
	virtual void Render();
	virtual void Update(double dt);
	virtual void ResetState();
	virtual void OnCollision(Entity* impactor, Entity::SideCollision side);
	virtual EnemyState::State GetState();
	
};

