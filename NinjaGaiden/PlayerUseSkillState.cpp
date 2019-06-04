#include "PlayerUseSkillState.h"
#include "Textures.h"

PlayerUseSkillState::PlayerUseSkillState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 3, 3, 3, 10, 4, 0.1f);
}

PlayerUseSkillState::~PlayerUseSkillState() {
}

void PlayerUseSkillState::Update(double dt) {
	m_Animation->Update(dt);
	int currentFrame = m_Animation->GetCurrentFrameID();
	if (m_Animation->IsLastFrame(dt)) // Cai nay khong biet da dung chua
	{
		playerData->player->SetState(Idle);
	}
	if (currentState >= currentFrame)
		return;
}

void PlayerUseSkillState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerUseSkillState::HandleInput() {
	KeyBoard* keyboard = KeyBoard::GetInstance();
	//Hung xu ly ho cac truong hop Input
}

void PlayerUseSkillState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	if (impactor->GetType() == Entity::EnemyType && playerData->player->timeHurtingAnimation == 0)
	{
		playerData->player->SetState(Beaten);
		return;
	}
}

PlayerState::State PlayerUseSkillState::GetState() {
	return UseSkill;
}

void PlayerUseSkillState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-9);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);

	PlayerState::ResetState(dummy);
}
