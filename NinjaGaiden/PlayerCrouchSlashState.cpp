#include "PlayerCrouchSlashState.h"
#include "Textures.h"

PlayerCrouchSlashState::PlayerCrouchSlashState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 7, 7, 3, 10, 4, 0.1f);

}

PlayerCrouchSlashState::~PlayerCrouchSlashState() {
}

void PlayerCrouchSlashState::Update(double dt) {
	if (m_Animation->IsLastFrame(dt)) {
		if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
			playerData->player->SetState(Crouch);
		else
			playerData->player->SetState(Crouch);
		return;
	}
	m_Animation->Update(dt);
}

void PlayerCrouchSlashState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerCrouchSlashState::HandleInput() {
	auto keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKeyDown(DIK_F))
		playerData->player->SetState(Jumping);
	else
		playerData->player->SetVelocity(D3DXVECTOR2(0, 0));
}

void PlayerCrouchSlashState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	if ((impactor->GetType() == Entity::EnemyType ||impactor->GetType()==Entity::EnemyWeaponType)&& playerData->player->timeHurtingAnimation == 0)
	{
		playerData->player->SetState(Beaten);
		return;
	}
}

PlayerState::State PlayerCrouchSlashState::GetState() {
	return CrouchSlash;
}

void PlayerCrouchSlashState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-12);
	player->SetColliderTop(8);
	player->SetColliderBottom(-16);
	PlayerState::ResetState(dummy);
}
