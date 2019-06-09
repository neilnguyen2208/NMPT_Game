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
};