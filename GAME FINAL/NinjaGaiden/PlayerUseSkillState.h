#pragma once
#include "PlayerState.h"
#include "PlayerData.h"
#include "Player.h"
#include "BlueShuriken.h"
#include"Grid.h"
#include"Unit.h"
#include"RedShuriken.h"
#include"FlameWheel.h"
#include"RyuWeapon.h"
class PlayerUseSkillState : public PlayerState {
public:
	PlayerUseSkillState(PlayerData *data);
	~PlayerUseSkillState();
	virtual void Update(double dt);
	virtual void Render();
	virtual void HandleInput();
	virtual void OnCollision(Entity *impactor, Entity::SideCollision side);
	virtual State GetState();
	virtual void ResetState(int dummy);

private:
	
	RyuWeapon*ryuWeapon_Turn1;
	RyuWeapon*ryuWeapon_Turn2;
	RyuWeapon*ryuWeapon_Turn3;
};