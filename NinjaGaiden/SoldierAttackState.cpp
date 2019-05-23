#include "SoldierAttackState.h"
#include "Enemy.h"

SoldierAttackState::SoldierAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SOLDIER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, SOLDIER_ATTACK_FRAME * (1 / 60.0f));
}

SoldierAttackState::~SoldierAttackState() {
}

void SoldierAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);
	//met moi vai c
	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();
	enemy->SetVx(0);
	EnemyState::ResetState();
}

void SoldierAttackState::Update(double dt) {
	m_Animation->Update(dt);
	if (m_Animation->GetPercentTime() >= SOLDIER_ATTACK_PERCENTTIME)
		enemyData->enemy->SetState(EnemyState::Follow);
}
