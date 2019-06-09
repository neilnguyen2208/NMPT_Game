#include "SoldierFollowState.h"
#include "Enemy.h"

SoldierFollowState::SoldierFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SOLDIER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 2, 2, 2, SOLDIER_FOLLOW_FRAME * (1 / 60.0f));
}

SoldierFollowState::~SoldierFollowState() {
}

void SoldierFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();

	if (Player::GetInstance()->GetPosition().x < enemy->GetPosition().x)
		enemy->SetVx(-SOLDIER_SPEED);
	else
		enemy->SetVx(SOLDIER_SPEED);

	EnemyState::ResetState();
}

void SoldierFollowState::Update(double dt) {
	m_Animation->Update(dt);
	if (m_Animation->GetPercentTime() >= SOLDIER_FOLLOW_PERCENTTIME)
		enemyData->enemy->SetState(EnemyState::Attack);
}

EnemyState::State SoldierFollowState::GetState()
{
	return Follow;
}

