#pragma once

#include "PlayerState.h"
#include "PlayerData.h"
#include "Player.h"

class PlayerBeatenState: public PlayerState{
public:
	PlayerBeatenState(PlayerData*data);
	~PlayerBeatenState();
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);

private:
	D3DXVECTOR2 acceleration;
	int currentState;
};

