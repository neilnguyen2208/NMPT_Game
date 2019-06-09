#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(PlayerData * data) {
	this->playerData = data;
}

PlayerState::PlayerState() {
}

PlayerState::~PlayerState() {
}

void PlayerState::Update(double dt) {
	m_Animation->Update(dt);
}

void PlayerState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerState::HandleInput() {
}

void PlayerState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	switch (impactor->GetTag())
	{
	case Entity::Sparta:
		playerData->player->score += 100;
		break;
		//case Entity::Cat:
		//	score += 200;
		//	break;
		//case Entity::Soldier:
		//	score += 200;
		//	break;
		//case Entity::Eagle:
		//	score += 300;
		//	break;
		//case Entity::Thrower:
		//	score += 300;
		//	break;
	}
}

PlayerState::State PlayerState::GetState() {
	return Idle;
}

int PlayerState::GetAnimationHeight() {
	return m_Animation->GetHeightCurrentFrame();
}

int PlayerState::GetAnimationWidth() {
	return m_Animation->GetWidthCurrentFrame();
}

void PlayerState::ResetState(int dummy) {
	m_Animation->ResetAnimation();
}