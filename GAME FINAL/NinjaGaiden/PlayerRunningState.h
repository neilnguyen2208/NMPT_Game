#pragma once
#include "PlayerState.h"
#include "Player.h"
#include "Textures.h"

class PlayerRunningState : public PlayerState {
public:
	PlayerRunningState(PlayerData *data);
	~PlayerRunningState();
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);
};