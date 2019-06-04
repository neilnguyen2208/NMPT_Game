#pragma once
#include "ItemState.h"
#include "Textures.h"
#include "Animation.h"

class ItemHolderState : public ItemState {
public:
	ItemHolderState(ItemData *data);
	~ItemHolderState();
	virtual void ResetState();
	virtual void Update(double dt);
	/*virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();*/
};