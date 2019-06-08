#include "SoldierAttackState.h"
#include "Enemy.h"

SoldierAttackState::SoldierAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SOLDIER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, SOLDIER_ATTACK_FRAME * (1 / 60.0f));
	turn = FirstTurn;
	soldierBullet_1 = new SoldierBullet();
	soldierBullet_2 = new SoldierBullet();
	soldierBullet_3 = new SoldierBullet();
	soldierBullet_4 = new SoldierBullet();
	soldierBullet_5 = new SoldierBullet();
	soldierBullet_6 = new SoldierBullet();
	grid = Grid::GetInstance(BoxCollider(224, 0, 0, 2048));
}

SoldierAttackState::~SoldierAttackState() {
}

void SoldierAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);
	//met moi vai c
	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();
	enemy->SetVx(0);
	EnemyState::ResetState();
}

void SoldierAttackState::Update(double dt) {
	m_Animation->Update(dt);
	
	//First turn
	if ((m_Animation->GetPercentTime() > 0.2&& m_Animation->GetPercentTime() < 0.3) && turn == FirstTurn)
	{
		soldierBullet_1->SetActive(true);
		soldierBullet_1->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_1->SetPosition(enemyData->enemy->GetPosition().x + 12, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_1->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_1->SetPosition(enemyData->enemy->GetPosition().x - 12, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_1->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}
		soldierBullet_1->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, soldierBullet_1);
	}
	else
	{
		soldierBullet_1->SetActive(false);
	}

	if ((m_Animation->GetPercentTime() > 1.2 && m_Animation->GetPercentTime() < 1.3) && turn == FirstTurn)
	{
		soldierBullet_2->SetActive(true);
		soldierBullet_2->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_2->SetPosition(enemyData->enemy->GetPosition().x + 6, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_2->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_2->SetPosition(enemyData->enemy->GetPosition().x - 6, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_2->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}
		soldierBullet_2->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, soldierBullet_2);
	}
	else
	{
		soldierBullet_2->SetActive(false);
	}

	if ((m_Animation->GetPercentTime() > 2.2 && m_Animation->GetPercentTime() < 2.3) && turn == FirstTurn)
	{
		soldierBullet_3->SetActive(true);
		soldierBullet_3->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_3->SetPosition(enemyData->enemy->GetPosition().x + 0, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_3->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_3->SetPosition(enemyData->enemy->GetPosition().x - 0, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_3->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}

		soldierBullet_3->SetAliveState(Entity::Alive);
		Unit*unit;
		unit = new Unit(grid, soldierBullet_3);
	}
	else
	{
		soldierBullet_3->SetActive(false);
	}

	//Second turn
	if ((m_Animation->GetPercentTime() > 0.2&& m_Animation->GetPercentTime() < 0.3) && turn == SecondTurn)
	{
		soldierBullet_4->SetActive(true);
		soldierBullet_4->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_4->SetPosition(enemyData->enemy->GetPosition().x + 12, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_4->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_4->SetPosition(enemyData->enemy->GetPosition().x - 12, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_4->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}

		soldierBullet_4->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, soldierBullet_4);
	}
	else
	{
		soldierBullet_4->SetActive(false);
	}

	if ((m_Animation->GetPercentTime() > 1.2 && m_Animation->GetPercentTime() < 1.3) && turn == SecondTurn)
	{
		soldierBullet_5->SetActive(true);
		soldierBullet_5->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_5->SetPosition(enemyData->enemy->GetPosition().x + 6, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_5->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_5->SetPosition(enemyData->enemy->GetPosition().x - 6, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_5->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}

		soldierBullet_5->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, soldierBullet_5);
	}
	else
	{
		soldierBullet_5->SetActive(false);
	}

	if ((m_Animation->GetPercentTime() > 2.2 && m_Animation->GetPercentTime() < 2.3) && turn == SecondTurn)
	{
		soldierBullet_6->SetActive(true);
		soldierBullet_6->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_6->SetPosition(enemyData->enemy->GetPosition().x + 0, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_6->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_6->SetPosition(enemyData->enemy->GetPosition().x - 0, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_6->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}

		soldierBullet_6->SetAliveState(Entity::Alive);
		Unit*unit;
		unit = new Unit(grid, soldierBullet_6);
	}
	else
	{
		soldierBullet_6->SetActive(false);
	}

	if (m_Animation->GetPercentTime() >= SOLDIER_ATTACK_PERCENTTIME)
	{
		if (turn == FirstTurn)
			turn = SecondTurn;
		else
			if (turn == SecondTurn)
				turn = FirstTurn;
		enemyData->enemy->SetState(EnemyState::Follow);
	}
}

EnemyState::State SoldierAttackState::GetState()
{
	return Attack;
}
void SoldierAttackState::SetTurn(Turn turn)
{
	this->turn = turn;
}

SoldierAttackState::Turn SoldierAttackState::GetTurn()
{
	return this->turn;
}
