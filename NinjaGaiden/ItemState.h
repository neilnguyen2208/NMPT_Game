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
	~ItemState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual void ResetState();
	virtual int GetAnimationHeight();
	virtual int GetAnimationWidth();
	Animation *GetAnimation() { return m_Animation; }

protected:
	ItemState(ItemData *data);
	ItemState();
	Animation *m_Animation;
	ItemData *itemData;
};
