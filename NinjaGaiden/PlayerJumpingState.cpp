#include "PlayerJumpingState.h"
#include "Textures.h"

PlayerJumpingState::PlayerJumpingState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 8, 8, 4, 10, 4, PLAYER_JUMPING_FRAME * (1.0f/60));
}

PlayerJumpingState::~PlayerJumpingState() {
}

void PlayerJumpingState::Render() {
	m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerJumpingState::HandleInput() {
	auto player = playerData->player;
	auto keyboard = KeyBoard::GetInstance();
	if (keyboard->GetKeyDown(DIK_D)) {
		player->SetState(Slash, 1);
		return;
	}
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

	player->AddVy(-GRAVITY);
	if (player->GetVelocity().y < 0)
		int x = 0;
	if (player->GetVelocity().y <= PLAYER_MAX_FALLING_VELOCITY) {
		player->SetVy(PLAYER_MAX_FALLING_VELOCITY);
	}
}

void PlayerJumpingState::OnCollision(Entity * impactor, Entity::SideCollision side) {	
	if (impactor->GetType() == Entity::EnemyType && playerData->player->timeHurtingAnimation == 0)
	{
		playerData->player->SetState(Beaten);
		return;
	}
	if (impactor->GetTag() == Entity::Ground && side == Entity::Bottom) {
		auto keyboard = KeyBoard::GetInstance();
		if (keyboard->GetKey(DIK_LEFTARROW) && !(keyboard->GetKey(DIK_RIGHTARROW)))
			playerData->player->SetState(Running);
		else
			if (keyboard->GetKey(DIK_RIGHTARROW) && !(keyboard->GetKey(DIK_LEFTARROW)))
				playerData->player->SetState(Running);
			else
				if (keyboard->GetKey(DIK_DOWNARROW))
					playerData->player->SetState(Crouch);
				else
					playerData->player->SetState(Idle);
		playerData->player->onAir = false;
		//OutputDebugString(L"Jumping to ground\n");
	}
}

PlayerState::State PlayerJumpingState::GetState() {
	return (playerData->player->GetVelocity().y > 0) ? Jumping : Falling;
}

void PlayerJumpingState::ResetState(int dummy) {
	auto player = playerData->player;
	player->SetColliderLeft(-9);
	player->SetColliderTop(16);
	player->SetColliderBottom(-6);

	//dummy = 0: back to this state from slash or something else 
	if (!player->onAir)
		playerData->player->SetVy(PLAYER_MIN_JUMP_VELOCITY);
	currentState = 0;
	player->onAir = true;

	PlayerState::ResetState(dummy);
}
