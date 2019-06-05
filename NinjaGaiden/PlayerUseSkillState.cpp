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
	if (m_Animation->IsLastFrame(dt)) {
		if (playerData->player->onAir)
			playerData->player->SetState(Falling);
		else
			if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
				playerData->player->SetState(Crouch);
			else
				playerData->player->SetState(Idle);
		return;
	}
	m_Animation->Update(dt);
}

void PlayerUseSkillState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerUseSkillState::HandleInput() {
	KeyBoard* keyboard = KeyBoard::GetInstance();
	auto player = playerData->player;

	if (keyboard->GetKeyDown(DIK_F) && !player->onAir)
		player->SetState(Jumping);
	else
		if (player->onAir) {

			if (keyboard->GetKey(DIK_LEFTARROW) && !keyboard->GetKey(DIK_RIGHTARROW)) {
				if (player->GetMoveDirection() == Player::RightToLeft)
					player->SetVx(-PLAYER_RUN_VELOCITY);
				else {
					player->SetVx(-PLAYER_RUN_VELOCITY / 3.0f);
					player->SetMoveDirection(Player::LeftToRight);
				}
			}
			else
				if (keyboard->GetKey(DIK_RIGHTARROW) && !keyboard->GetKey(DIK_LEFTARROW)) {
					if (player->GetMoveDirection() == Player::LeftToRight)
						player->SetVx(PLAYER_RUN_VELOCITY);
					else {
						player->SetVx(PLAYER_RUN_VELOCITY / 3.0f);
						player->SetMoveDirection(Player::RightToLeft);
					}
				}
				else player->SetVx(0);

			float vy = player->GetVelocity().y;
			player->AddVy(-GRAVITY);
			if (player->GetVelocity().y <= PLAYER_MAX_FALLING_VELOCITY) {
				player->SetVy(PLAYER_MAX_FALLING_VELOCITY);
			}
		}

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
