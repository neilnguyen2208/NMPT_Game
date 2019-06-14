#include "SpartaFollowState.h"
#include "Enemy.h"

SpartaFollowState::SpartaFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SPARTA);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 4, SPARTA_FRAME * (1/60.0f));
}

SpartaFollowState::~SpartaFollowState() {
}

void SpartaFollowState::ResetState() {

	auto enemy = enemyData->enemy;
	auto enemyX = enemy->GetPosition().x;
	auto playerX = Player::GetInstance()->GetPosition().x;

	if (playerX > enemyX)
		enemy->SetVx(SPARTA_SPEED);
	else
		enemy->SetVx(-SPARTA_SPEED);

	enemy->SetColliderTop(12);
	enemy->SetColliderBottom(-21);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();

	EnemyState::ResetState();
}

void SpartaFollowState::Update(double dt) {
	m_Animation->Update(dt);
}
