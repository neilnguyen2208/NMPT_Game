#pragma once
#include "Entity.h"
#include "ItemData.h"
#include "GameConfig.h"
#include "Camera.h"
#include "ItemState.h"
#include "Textures.h"

class Item : public Entity {
public:

	Item(Entity::EntityTag tagItem);
	~Item();
	virtual void Update(double dt);
	virtual void Render();
	void SetState(ItemState::State name);
	void OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime);

	virtual BoxCollider GetRect();

	virtual void SetMoveDirection(Entity::EntityDirection dir);

	virtual void SetActive(bool active);

	virtual void SetSpawnBox(BoxCollider box, int direction);
	virtual void Spawn();
	virtual float GetWidth();
	virtual float GetHeight();
	virtual void MakeInactive();
	virtual void SetColliderTop(int top);
	virtual void SetColliderLeft(int left);
	virtual void SetColliderBottom(int bottom);
	virtual void SetColliderRight(int right);

protected:
	ItemData *itemData;
	ItemState
		*itemAvailableState,
		*itemHolderState;
	Entity::EntityDirection spawnDirection;
	BoxCollider collider;
	D3DXVECTOR3 spawnPosition;
	BoxCollider spawnBox;
	float collisionTime;
	SideCollision side;
	int timelimit = 0;

};


