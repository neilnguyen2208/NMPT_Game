#include "PlayerUseItemState.h"
#include "Textures.h"

PlayerUseItemState::PlayerUseItemState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 3, 3, 3, 9, 4, 0.1f);
}

PlayerUseItemState::~PlayerUseItemState() {
}

void PlayerUseItemState::Update(double dt) {
	m_Animation->Update(dt);
	int currentFrame = m_Animation->GetCurrentFrameID();
	if (currentState >= currentFrame)
		return;
}

void PlayerUseItemState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerUseItemState::HandleInput() {

}

void PlayerUseItemState::OnCollision(Entity * impactor, Entity::SideCollision side) {
}

PlayerState::State PlayerUseItemState::GetState() {
	return UseItem;
}

void PlayerUseItemState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-9);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);
	PlayerState::ResetState(dummy);
}
