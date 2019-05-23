#pragma once
#include "PlayerState.h"
#include "PlayerData.h"
#include "Player.h"

class PlayerClimbState : public PlayerState {
public:
	PlayerClimbState(PlayerData *data);
	~PlayerClimbState();
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);
	//Animation *GetAnimation() { return m_Animation; }
};