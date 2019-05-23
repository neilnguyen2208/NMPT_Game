#pragma once
#include "Entity.h"
#include "Animation.h"
#include "ItemData.h"
#include "GameConfig.h"

class ItemState {
public:
	enum State {
		Unavailable,
		Available
	};
	ItemState(ItemData *data);
	ItemState();
	~ItemState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual void ResetState();
protected:
	Animation *m_Animation;
	ItemData *itemData;
};
