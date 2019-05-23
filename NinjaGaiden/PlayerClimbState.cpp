#include "PlayerClimbState.h"
#include "Textures.h"

PlayerClimbState::PlayerClimbState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 4, 4, 1, 9, 4, 0.1f);
}

PlayerClimbState::~PlayerClimbState() {
}

void PlayerClimbState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerClimbState::HandleInput() {

}

void PlayerClimbState::OnCollision(Entity * impactor, Entity::SideCollision side) {
}

PlayerState::State PlayerClimbState::GetState() {
	return Climb;
}

void PlayerClimbState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-9);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);
	PlayerState::ResetState(dummy);
}
