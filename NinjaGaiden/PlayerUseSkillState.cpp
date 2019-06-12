#include "PlayerUseSkillState.h"
#include "Textures.h"

PlayerUseSkillState::PlayerUseSkillState(PlayerData * data) {
	this->playerData = data;
	auto texs = Textures::GetInstance();
	m_Animation = new Animation();
	m_Animation->AddFramesA(texs->Get(TEX_PLAYER), 3, 3, 3, 10, 4, 0.15f);
	turn = FirstTurn;
	grid = Grid::GetInstance(BoxCollider(224, 0, 0, 2048));
}

PlayerUseSkillState::~PlayerUseSkillState() {
}

void PlayerUseSkillState::Update(double dt) {

	m_Animation->Update(dt);
	//DebugOut(L"%f\n", m_Animation->GetPercentTime());
	int currentFrame = m_Animation->GetCurrentFrameID();
	if (playerData->player->GetSkill() == Player::NoneSkill)
		if (m_Animation->IsLastFrame(dt))
			playerData->player->SetState(Idle);

	if (playerData->player->GetSkill() == Player::BlueShurikenSkill && playerData->player->power >= 3)
	{
		//	DebugOut(L"%f\n", m_Animation->GetPercentTime());
		ryuWeapon_Turn1 = new BlueShuriken();
		ryuWeapon_Turn2 = new BlueShuriken();
		ryuWeapon_Turn3 = new BlueShuriken();


		//First turn
		if ((m_Animation->GetPercentTime() > 0.03&& m_Animation->GetPercentTime() < 0.04) && turn == FirstTurn)
		{
			CSoundChoose::GetInstance()->PlaySoundChoose(12); //âm thanh sử dụng SkillBlue
			playerData->player->power -= 3;
			ryuWeapon_Turn1->SetActive(true);
			ryuWeapon_Turn1->SetMoveDirection(playerData->player->GetMoveDirection());
			if (playerData->player->GetMoveDirection() == Entity::LeftToRight) {
				ryuWeapon_Turn1->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //	
				ryuWeapon_Turn1->SetVx((BLUE_SHURIKEN_VELOCITY_X));
			}
			else
			{
				ryuWeapon_Turn1->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //	
				ryuWeapon_Turn1->SetVx((-BLUE_SHURIKEN_VELOCITY_X));
			}
			ryuWeapon_Turn1->SetAliveState(Entity::Alive);
			Unit* unit;
			unit = new Unit(grid, ryuWeapon_Turn1);
		}
		else
		{
			ryuWeapon_Turn1->SetActive(false);
		}

		//Second Turn
		if ((m_Animation->GetPercentTime() > 0.03&& m_Animation->GetPercentTime() < 0.04) && turn == SecondTurn)
		{
			CSoundChoose::GetInstance()->PlaySoundChoose(12); //âm thanh sử dụng SkillBlue
			playerData->player->power -= 3;
			ryuWeapon_Turn2->SetActive(true);
			ryuWeapon_Turn2->SetMoveDirection(playerData->player->GetMoveDirection());
			if (playerData->player->GetMoveDirection() == Entity::LeftToRight) {
				ryuWeapon_Turn2->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //	
				ryuWeapon_Turn2->SetVx((BLUE_SHURIKEN_VELOCITY_X));
			}
			else // 8 6
			{
				ryuWeapon_Turn2->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //	
				ryuWeapon_Turn2->SetVx((-BLUE_SHURIKEN_VELOCITY_X));
			}
			ryuWeapon_Turn2->SetAliveState(Entity::Alive);
			Unit* unit;
			unit = new Unit(grid, ryuWeapon_Turn2);
		}
		else
		{
			ryuWeapon_Turn2->SetActive(false);
		}

		//Third Turn
		if ((m_Animation->GetPercentTime() > 0.03&& m_Animation->GetPercentTime() < 0.04) && turn == ThirdTurn)
		{
			CSoundChoose::GetInstance()->PlaySoundChoose(12); //âm thanh sử dụng SkillBlue
			playerData->player->power -= 3;
			ryuWeapon_Turn3->SetActive(true);
			ryuWeapon_Turn3->SetMoveDirection(playerData->player->GetMoveDirection());
			if (playerData->player->GetMoveDirection() == Entity::LeftToRight) {
				ryuWeapon_Turn3->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //	
				ryuWeapon_Turn3->SetVx((BLUE_SHURIKEN_VELOCITY_X));
			}
			else // 8 6
			{
				ryuWeapon_Turn3->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //	
				ryuWeapon_Turn3->SetVx((-BLUE_SHURIKEN_VELOCITY_X));
			}
			ryuWeapon_Turn3->SetAliveState(Entity::Alive);
			Unit* unit;
			unit = new Unit(grid, ryuWeapon_Turn3);
		}
		else
		{
			ryuWeapon_Turn3->SetActive(false);
		}


		if (m_Animation->IsLastFrame(dt)) // Cai nay khong biet da dung chua
		{
			if (turn == FirstTurn)
				turn = SecondTurn;
			else if (turn == SecondTurn)
				turn = ThirdTurn;
			else if (turn == ThirdTurn)
				turn = FirstTurn;
			if (playerData->player->onAir)
				playerData->player->SetState(Falling);
			else
				if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
					playerData->player->SetState(Crouch);
				else
					playerData->player->SetState(Idle);
		}
		return;
	}
	else
		if (playerData->player->GetSkill() == Player::RedShurikenSkill && playerData->player->power >= 5)
		{
			ryuWeapon_Turn1 = new RedShuriken();

			if ((m_Animation->GetPercentTime() > 0.03&& m_Animation->GetPercentTime() < 0.04))
			{
				CSoundChoose::GetInstance()->PlaySoundChoose(13); //âm thanh sử dụng SkillRed
				playerData->player->power -= 5;
				ryuWeapon_Turn1->SetActive(true);
				//	ryuWeapon_Turn1->SetMoveDirection(playerData->player->GetMoveDirection());
				if (playerData->player->GetMoveDirection() == Entity::LeftToRight) {
					ryuWeapon_Turn1->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //	
					ryuWeapon_Turn1->SetVx((RED_SHURIKEN_VELOCITY_X));
				}
				else
				{
					ryuWeapon_Turn1->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //	
					ryuWeapon_Turn1->SetVx((-RED_SHURIKEN_VELOCITY_X));
				}

				ryuWeapon_Turn1->SetAliveState(Entity::Alive);
				Unit* unit;
				unit = new Unit(grid, ryuWeapon_Turn1);
			}
			else
			{
				ryuWeapon_Turn1->SetActive(false);
			}
			if (m_Animation->IsLastFrame(dt)) // Cai nay khong biet da dung chua
			{
				if (playerData->player->onAir)
					playerData->player->SetState(Falling);
				else
					if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
						playerData->player->SetState(Crouch);
					else
						playerData->player->SetState(Idle);
			}
			return;
		}
		else
			if (playerData->player->GetSkill() == Player::Skill::FlameWheelSkill && playerData->player->power >= 5)
			{
				ryuWeapon_Turn1 = new FlameWheel();
				ryuWeapon_Turn2 = new FlameWheel();
				ryuWeapon_Turn3 = new FlameWheel();

				//First turn
				if ((m_Animation->GetPercentTime() > 0.03&& m_Animation->GetPercentTime() < 0.04))
				{
					CSoundChoose::GetInstance()->PlaySoundChoose(14); //âm thanh sử dụng SkillFlame
					playerData->player->power -= 5;
					ryuWeapon_Turn1->SetActive(true);
					ryuWeapon_Turn2->SetActive(true);
					ryuWeapon_Turn3->SetActive(true);
					ryuWeapon_Turn1->SetMoveDirection(playerData->player->GetMoveDirection());
					ryuWeapon_Turn2->SetMoveDirection(playerData->player->GetMoveDirection());
					ryuWeapon_Turn3->SetMoveDirection(playerData->player->GetMoveDirection());
					if (playerData->player->GetMoveDirection() == Entity::LeftToRight) {
						ryuWeapon_Turn1->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //	
						ryuWeapon_Turn2->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //
						ryuWeapon_Turn3->SetPosition(playerData->player->GetPosition().x + 22, playerData->player->GetPosition().y + 6); //
						ryuWeapon_Turn1->SetVx(FLAME_WHEEL_1_VELOCITY_X);
						ryuWeapon_Turn1->SetVy(FLAME_WHEEL_1_VELOCITY_Y);
						ryuWeapon_Turn2->SetVx(FLAME_WHEEL_2_VELOCITY_X);
						ryuWeapon_Turn2->SetVy(FLAME_WHEEL_2_VELOCITY_Y);
						ryuWeapon_Turn3->SetVx(FLAME_WHEEL_3_VELOCITY_X);
						ryuWeapon_Turn3->SetVy(FLAME_WHEEL_3_VELOCITY_Y);
					}
					else
					{
						ryuWeapon_Turn1->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //	
						ryuWeapon_Turn2->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //
						ryuWeapon_Turn3->SetPosition(playerData->player->GetPosition().x - 22, playerData->player->GetPosition().y + 6); //
						ryuWeapon_Turn1->SetVx(-FLAME_WHEEL_1_VELOCITY_X);
						ryuWeapon_Turn1->SetVy(FLAME_WHEEL_1_VELOCITY_Y);
						ryuWeapon_Turn2->SetVx(-FLAME_WHEEL_2_VELOCITY_X);
						ryuWeapon_Turn2->SetVy(FLAME_WHEEL_2_VELOCITY_Y);
						ryuWeapon_Turn3->SetVx(-FLAME_WHEEL_3_VELOCITY_X);
						ryuWeapon_Turn3->SetVy(FLAME_WHEEL_3_VELOCITY_Y);
					}
					ryuWeapon_Turn1->SetAliveState(Entity::Alive);
					ryuWeapon_Turn2->SetAliveState(Entity::Alive);
					ryuWeapon_Turn3->SetAliveState(Entity::Alive);
					Unit* unit_1;
					Unit* unit_2;
					Unit* unit_3;
					unit_1 = new Unit(grid, ryuWeapon_Turn1);
					unit_2 = new Unit(grid, ryuWeapon_Turn2);
					unit_3 = new Unit(grid, ryuWeapon_Turn3);
				}
				else
				{
					ryuWeapon_Turn1->SetActive(false);
					ryuWeapon_Turn2->SetActive(false);
					ryuWeapon_Turn3->SetActive(false);
				}

				if (m_Animation->IsLastFrame(dt)) // Cai nay khong biet da dung chua
				{
					if (playerData->player->onAir)
						playerData->player->SetState(Falling);
					else
						if (KeyBoard::GetInstance()->GetKey(DIK_DOWNARROW))
							playerData->player->SetState(Crouch);
						else
							playerData->player->SetState(Idle);
				}
				return;
			}

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
	if ((impactor->GetType() == Entity::EnemyType||impactor->GetType()==Entity::EnemyWeaponType) && playerData->player->timeHurtingAnimation == 0)
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
