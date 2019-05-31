#include "PlayerCrouchState.h"
#include "Textures.h"

PlayerCrouchState::PlayerCrouchState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 6, 6, 1, 10, 4, 0.1f);

}

PlayerCrouchState::~PlayerCrouchState() {
}

void PlayerCrouchState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerCrouchState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	//CrouchSlash, Slash, Jump, Running, Idle,...?
	if (keyboard->GetKeyDown(DIK_D) && keyboard->GetKey(DIK_DOWNARROW))
		playerData->player->SetState(CrouchSlash);
	else
		if (keyboard->GetKeyDown(DIK_D) && !keyboard->GetKey(DIK_DOWNARROW))
			playerData->player->SetState(Slash);
		else
			if (keyboard->GetKeyDown(DIK_F))
				playerData->player->SetState(Jumping);
			else
				if (keyboard->GetKey(DIK_LEFT) && !keyboard->GetKey(DIK_RIGHT)) 
					playerData->player->SetState(Running);
				else
					if (keyboard->GetKey(DIK_RIGHT) && !keyboard->GetKey(DIK_LEFT))
						playerData->player->SetState(Running);
					else if (!keyboard->GetKey(DIK_DOWNARROW))
						playerData->player->SetState(Idle);
}

void PlayerCrouchState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	if (impactor->GetType() == Entity::EnemyType && playerData->player->timeHurtingAnimation == 0)
	{
		playerData->player->SetState(Beaten);
		return;
	}
}

PlayerState::State PlayerCrouchState::GetState() {
	return Crouch;
}

void PlayerCrouchState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-9);
	player->SetColliderTop(8);
	player->SetColliderBottom(-16);
	PlayerState::ResetState(dummy);
}
