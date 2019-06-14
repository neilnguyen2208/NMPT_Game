#include "PlayerClimbState.h"
#include "Textures.h"
#include"ExternalDataCollector.h"
PlayerClimbState::PlayerClimbState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 4, 4, 1, 10, 4, 0.1f);
	isClimb = false;
	climb_Animaition = new Animation();
	climb_Animaition->AddFramesA(texs->Get(TEX_PLAYER), 4, 4, 2, 10, 4, 0.1f);
}

PlayerClimbState::~PlayerClimbState() {
}

void PlayerClimbState::Render() {
	if (isClimb)
	{
		climb_Animaition->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
	}
	else
		m_Animation->Render(playerData->player->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), playerData->player->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void PlayerClimbState::HandleInput() {
	//xu ly theo priority nghe, Slash, Jump, Running, Crouch,... ?
}

void PlayerClimbState::OnCollision(Entity * impactor, Entity::SideCollision side) {
	if ((impactor->GetType() == Entity::EnemyType || impactor->GetType() == Entity::EnemyWeaponType) && playerData->player->timeHurtingAnimation == 0)
	{
		playerData->player->SetState(Beaten);
		return;
	}
	KeyBoard* keyboard = KeyBoard::GetInstance();
	if (impactor->GetTag() == Entity::ClimbWall)
	{	
			if (keyboard->GetKey(DIK_DOWNARROW))
			{
				if (playerData->player->GetRect().bottom >= impactor->GetRect().bottom)
					playerData->player->SetVy(-PLAYER_CLIMB_VELOCITY);
				else
					playerData->player->SetVy(0);
				isClimb = true;
			}
			else if (keyboard->GetKey(DIK_UPARROW))
			{
				if (playerData->player->GetRect().top <= impactor->GetRect().top)
					playerData->player->SetVy(PLAYER_CLIMB_VELOCITY);
				else
					playerData->player->SetVy(0);
				isClimb = true;
			}
			else
			{
				isClimb = false;
				playerData->player->SetVy(0); 
			}
	}

	if (side == Entity::SideCollision::Right&& (impactor->GetTag() == Entity::ClimbWall || impactor->GetTag() == Entity::Wall))
	{
		if (keyboard->GetKey(DIK_LEFTARROW))
		{
			if (keyboard->GetKeyDown(DIK_F))
			{
				ExternalDataCollector::GetInstance()->SetClimb(true);
				playerData->player->SetVelocity(D3DXVECTOR2(-PLAYER_RUN_VELOCITY, 0));
				playerData->player->SetVy(0.75f*PLAYER_MIN_JUMP_VELOCITY);
				playerData->player->SetState(Jumping);
				return;
			}
		}
	}
	else
		if (side == Entity::SideCollision::Left&&(impactor->GetTag() == Entity::ClimbWall||impactor->GetTag()==Entity::Wall))
		{
			if (keyboard->GetKey(DIK_RIGHTARROW))
			{
				if (keyboard->GetKeyDown(DIK_F))
				{
					ExternalDataCollector::GetInstance()->SetClimb(true);
					playerData->player->SetVelocity(D3DXVECTOR2(PLAYER_RUN_VELOCITY, 0));
					playerData->player->SetVy(0.75f*PLAYER_MIN_JUMP_VELOCITY);
					playerData->player->SetState(Jumping);
					return;
				}
			}
		}

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

void PlayerClimbState::Update(double dt)
{
	if (isClimb)
	{
		climb_Animaition->Update(dt);
	}
	else
		PlayerState::Update(dt);
}

