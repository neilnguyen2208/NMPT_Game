#pragma once
#include"Entity.h"
#include"Animation.h"
#include"Textures.h"

class EnemyWeapon :public Entity
{
public:

	float offsetScaleX;

	virtual void Update(double dt);
	virtual void Render();

	virtual BoxCollider GetRect();
	virtual BoxCollider GetSpawnRect();
	virtual void SetActive(bool active);
	virtual bool IsActive();
	virtual void SetRect(BoxCollider box);
	virtual void SetSpawnBox(BoxCollider box, int direction);
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);
	virtual void SetMoveDirection(Entity::EntityDirection dir);
	EntityDirection GetMoveDirection();

	//Get collilder width
	virtual float GetWidth();
	virtual float GetBigWidth();

	//Get collider height;
	virtual float GetHeight();
	virtual float GetBigHeight();
	virtual BoxCollider GetCollider();

	virtual void MakeInactive();
	virtual void Spawn();
	virtual Entity::EntityDirection GetSpawnDirection();
	EnemyWeapon();
	~EnemyWeapon();

protected:

	D3DXVECTOR3 spawnPosition;
	Entity::EntityDirection spawnDirection;
	BoxCollider spawnBox;
	BoxCollider collider;
	float collisionTime;
	SideCollision side;
	Animation* m_Animation;

};

