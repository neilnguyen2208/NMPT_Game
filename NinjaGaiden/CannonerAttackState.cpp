#include "CannonerAttackState.h"
#include "Enemy.h"

CannonerAttackState::CannonerAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_CANNONER);
	m_Animation = new Animation();
	m_AnimationAttack = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 2, 2, 2, CANNONER_FRAME * (1 / 60.0f));
	m_AnimationAttack->AddFramesA(texture, 2, 2, 2, 2, 2, CANNONER_ATTACK_FRAME*(1/60.0f));
	turn = FirstTurn;

	grid = Grid::GetInstance();
}

CannonerAttackState::~CannonerAttackState() {
}

void CannonerAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-16);
	enemy->SetColliderRight(16);
	//met moi vai c
	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();
	enemy->SetVx(0);
	EnemyState::ResetState();
}

void CannonerAttackState::Update(double dt) {
	m_Animation->Update(dt);
	//First turn
	if ((m_Animation->GetPercentTime() > 0.03&& m_Animation->GetPercentTime() < 0.04) && turn == FirstTurn)
	{
		CSoundChoose::GetInstance()->PlaySoundChoose(5); //âm thanh khi cannoner bắn 
		cannonerBullet_1 = new CannonerBullet();
		cannonerBullet_1->SetActive(true);
		cannonerBullet_1->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			cannonerBullet_1->SetPosition(enemyData->enemy->GetPosition().x + 12, enemyData->enemy->GetPosition().y + 0); //	
			cannonerBullet_1->SetVx((CANNONER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			cannonerBullet_1->SetPosition(enemyData->enemy->GetPosition().x - 12, enemyData->enemy->GetPosition().y + 0); //	
			cannonerBullet_1->SetVx((-CANNONER_BULLET_VELOCITY_X));
		}
		cannonerBullet_1->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, cannonerBullet_1);
	}
	
	if ((m_Animation->GetPercentTime() > 0.03 && m_Animation->GetPercentTime() < 0.04) && turn == SecondTurn)
	{
		CSoundChoose::GetInstance()->PlaySoundChoose(5); //âm thanh khi cannoner bắn 
		cannonerBullet_2 = new CannonerBullet();
		cannonerBullet_2->SetActive(true);
		cannonerBullet_2->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			cannonerBullet_2->SetPosition(enemyData->enemy->GetPosition().x + 6, enemyData->enemy->GetPosition().y + 0); //	
			cannonerBullet_2->SetVx((CANNONER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			cannonerBullet_2->SetPosition(enemyData->enemy->GetPosition().x - 6, enemyData->enemy->GetPosition().y + 0); //	
			cannonerBullet_2->SetVx((-CANNONER_BULLET_VELOCITY_X));
		}
		cannonerBullet_2->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, cannonerBullet_2);
	}
	
	if (m_Animation->GetPercentTime() >= CANNONER_ATTACK_PERCENTTIME)
	{
		if (turn == FirstTurn)
			turn = SecondTurn;
		else
			if(turn == SecondTurn)
			turn = FirstTurn;
		m_Animation->ResetAnimation();
	}
}

EnemyState::State CannonerAttackState::GetState()
{
	return Attack;
}

void CannonerAttackState::Render()
{
	if (m_Animation->GetPercentTime()>0.03&&m_Animation->GetPercentTime()<0.2)
	{
		m_AnimationAttack->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
	}
	else
		EnemyState::Render();
}
