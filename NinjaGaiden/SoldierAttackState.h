#pragma once
#include "EnemyState.h"
#include "Textures.h"
#include "Animation.h"
#include"EnemyWeapon.h"
#include"SoldierBullet.h"
#include"Unit.h"
#include"Grid.h"

class SoldierAttackState : public EnemyState {

	//First turn
	EnemyWeapon*soldierBullet_1;
	EnemyWeapon*soldierBullet_2;
	EnemyWeapon*soldierBullet_3;

	//Second Turn
	EnemyWeapon*soldierBullet_4;
	EnemyWeapon*soldierBullet_5;
	EnemyWeapon*soldierBullet_6;

	Grid*grid;
	enum Turn
	{
		FirstTurn,
		SecondTurn
	};

	Turn turn;

public:
	SoldierAttackState(EnemyData *data);
	~SoldierAttackState();
	virtual void ResetState();
	virtual void Update(double dt);
	virtual State GetState();

};