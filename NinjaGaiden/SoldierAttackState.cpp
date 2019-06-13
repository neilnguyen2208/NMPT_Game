#include "SoldierAttackState.h"
#include "Enemy.h"

SoldierAttackState::SoldierAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_SOLDIER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, SOLDIER_ATTACK_FRAME * (1 / 60.0f));
	
	grid = Grid::GetInstance();
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
	if ((m_Animation->GetPercentTime() > 0.2&& m_Animation->GetPercentTime() < 0.3) )
	{
		CSoundChoose::GetInstance()->PlaySoundChoose(4); //âm thanh khi solider b?n 
		soldierBullet_1 = new SoldierBullet();
		soldierBullet_1->SetActive(true);
		soldierBullet_1->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_1->SetPosition(enemyData->enemy->GetPosition().x + 16, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_1->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_1->SetPosition(enemyData->enemy->GetPosition().x - 16, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_1->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}
		soldierBullet_1->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, soldierBullet_1);
	}

	if ((m_Animation->GetPercentTime() > 1.2 && m_Animation->GetPercentTime() < 1.3))
	{
		CSoundChoose::GetInstance()->PlaySoundChoose(4); //âm thanh khi solider b?n 
		soldierBullet_2 = new SoldierBullet();
		soldierBullet_2->SetActive(true);
		soldierBullet_2->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_2->SetPosition(enemyData->enemy->GetPosition().x + 12, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_2->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_2->SetPosition(enemyData->enemy->GetPosition().x - 12, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_2->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}
		soldierBullet_2->SetAliveState(Entity::Alive);
		Unit* unit;
		unit = new Unit(grid, soldierBullet_2);
	}

	if ((m_Animation->GetPercentTime() > 2.2 && m_Animation->GetPercentTime() < 2.3))
	{
		CSoundChoose::GetInstance()->PlaySoundChoose(4); //âm thanh khi solider b?n 
		soldierBullet_3 = new SoldierBullet();
		soldierBullet_3->SetActive(true);
		soldierBullet_3->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			soldierBullet_3->SetPosition(enemyData->enemy->GetPosition().x + 8, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_3->SetVx((SOLDIER_BULLET_VELOCITY_X));
		}
		else // 8 6
		{
			soldierBullet_3->SetPosition(enemyData->enemy->GetPosition().x - 8, enemyData->enemy->GetPosition().y + 0); //	
			soldierBullet_3->SetVx((-SOLDIER_BULLET_VELOCITY_X));
		}

		soldierBullet_3->SetAliveState(Entity::Alive);
		Unit*unit;
		unit = new Unit(grid, soldierBullet_3);
	}

	if (m_Animation->GetPercentTime() >= SOLDIER_ATTACK_PERCENTTIME)
	{
		
		enemyData->enemy->SetState(EnemyState::Follow);
	}
}

EnemyState::State SoldierAttackState::GetState()
{
	return Attack;
}
