#pragma once
#include "Entity.h"
#include "EnemyData.h"
#include "GameConfig.h"
#include "EnemyState.h"
#include "Camera.h"
#include "Player.h"
#include "ThrowerBullet.h"
#include "Grid.h"

class Enemy : public Entity {
public:
	//--DEBUG--
	float offsetScaleX;

	Enemy();
	~Enemy();

	virtual void Update(double dt);
	virtual void Render();
	
	virtual BoxCollider GetRect();
	virtual BoxCollider GetSpawnRect();
	virtual void SetActive(bool active);
	virtual void SetRect(BoxCollider box);
	virtual void SetSpawnBox(BoxCollider box, int direction);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetMoveDirection(Entity::EntityDirection dir);
	virtual void SetState(EnemyState::State state);
	//Get collilder width
	virtual float GetWidth();
	virtual float GetBigWidth();
	//Get collider height;
	virtual float GetHeight();
	virtual float GetBigHeight();
	virtual BoxCollider GetCollider();
	virtual void OnCollision(Entity *impactor, SideCollision side, float collisionTime);
	virtual void MakeInactive();
	virtual void Spawn();
	virtual Entity::EntityDirection GetSpawnDirection();
	
protected:

	D3DXVECTOR3 spawnPosition;
	Entity::EntityDirection spawnDirection;
	BoxCollider spawnBox;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	EnemyData *enemyData;
	EnemyState *enemyBeatenState;

};