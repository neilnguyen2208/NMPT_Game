#pragma once
#include "PlayerState.h"
#include "PlayerData.h"
#include "Player.h"
#include"Grid.h"
#include"Unit.h"
#include "RyuWeapon.h"
#include"RedShuriken.h"
#include"BlueShuriken.h"
#include"FlameWheel.h"
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

	enum Turn
	{
		FirstTurn,
		SecondTurn,
		ThirdTurn
	};



private:
	Grid* grid;

	// for blue shuriken and flame wheel!
	// red shuriken's process way in all state, in PlayerState.h
	RyuWeapon*ryuWeapon_Turn1;
	RyuWeapon*ryuWeapon_Turn2;
	RyuWeapon*ryuWeapon_Turn3;

	Turn turn;
};