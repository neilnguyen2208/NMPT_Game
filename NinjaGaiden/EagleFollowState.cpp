#include "EagleFollowState.h"
#include "Enemy.h"

EagleFollowState::EagleFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_EAGLE);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 2, EAGLE_FRAME * (1 / 60.0f));
}

EagleFollowState::~EagleFollowState() {
}

void EagleFollowState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(12);
	enemy->SetColliderBottom(-12);
	enemy->SetColliderLeft(-8);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();
	enemy->SetVelocity(D3DXVECTOR2(0, 0));
	EnemyState::ResetState();
}

void EagleFollowState::Update(double dt) {
	m_Animation->Update(dt);
}
