#include "PlayerIdleState.h"
#include "Textures.h"

PlayerIdleState::PlayerIdleState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 1, 1, 1, 10, 4);
}

PlayerIdleState::~PlayerIdleState() {
}

void PlayerIdleState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerIdleState::HandleInput() {
	//xu ly theo priority nghe, Slash, Jump, Running, Crouch,... ?
	KeyBoard *keyboard = KeyBoard::GetInstance();
	bool isUseSkill = false;

	if (keyboard->GetKey(DIK_UPARROW))
	{
		isUseSkill = true;
	}

	if (keyboard->GetKeyDown(DIK_D))
	{
		if (isUseSkill)
		{
			playerData->player->SetState(UseSkill);
		}
		else
		playerData->player->SetState(Slash);
	}
	else
		if (keyboard->GetKeyDown(DIK_F))
			playerData->player->SetState(Jumping);
		else
			if (keyboard->GetKey(DIK_LEFTARROW) && !keyboard->GetKey(DIK_RIGHTARROW)) {
				playerData->player->SetState(Running, 0);
			}
			else
				if (keyboard->GetKey(DIK_RIGHTARROW) && !keyboard->GetKey(DIK_LEFTARROW)) {
					playerData->player->SetState(Running, 0);
				}
				else
					if (keyboard->GetKey(DIK_DOWNARROW))
						playerData->player->SetState(Crouch);
					else
						playerData->player->SetVelocity(D3DXVECTOR2(0, 0));

}

void PlayerIdleState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	if ((impactor->GetType() == Entity::EnemyType|| impactor->GetType() == Entity::EnemyWeaponType) && playerData->player->timeHurtingAnimation == 0)
	{
		playerData->player->SetState(Beaten);
		return;
	}
}

PlayerState::State PlayerIdleState::GetState() {
	return Idle;
}

void PlayerIdleState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-9);
	player->SetColliderTop(16);
	player->SetColliderBottom(-16);

	PlayerState::ResetState(dummy);
}
