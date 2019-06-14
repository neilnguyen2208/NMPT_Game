#include "ThrowerFollowState.h"
#include "Enemy.h"
#include<iostream>
ThrowerFollowState::ThrowerFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_THROWER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 2, 2, 2, THROWER_FRAME * (1 / 60.0f));
}

ThrowerFollowState::~ThrowerFollowState() {
}

void ThrowerFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	auto playerX = Player::GetInstance()->GetPosition().x;
	auto enemyX = enemy->GetPosition().x; 

	if (playerX > enemyX)
		enemy->SetVx(THROWER_SPEED);
	else
		enemy->SetVx(-THROWER_SPEED);

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(10);
	enemy->SetColliderBottom(-22);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();

	EnemyState::ResetState();
}

void ThrowerFollowState::Update(double dt) {
	m_Animation->Update(dt);
	if (m_Animation->GetPercentTime() >= 3.0f)
	{
		enemyData->enemy->SetState(EnemyState::Attack);
	}
}

EnemyState::State ThrowerFollowState::GetState()
{
	return Follow;
}


