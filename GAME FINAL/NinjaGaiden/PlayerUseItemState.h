#pragma once
#include "PlayerState.h"
#include "PlayerData.h"
#include "Player.h"

class PlayerUseItemState : public PlayerState {
public:
	PlayerUseItemState(PlayerData *data);
	~PlayerUseItemState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);
private:
	int currentState;
};