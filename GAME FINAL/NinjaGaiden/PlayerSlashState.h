#pragma once
#include "PlayerState.h"
#include "PlayerData.h"
#include "Player.h"

class PlayerSlashState : public PlayerState {
public:
	PlayerSlashState(PlayerData *data);
	~PlayerSlashState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);
};