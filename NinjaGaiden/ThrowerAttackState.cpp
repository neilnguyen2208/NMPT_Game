#include "ThrowerAttackState.h"
#include "Enemy.h"
#include"GameConfig.h"


ThrowerAttackState::ThrowerAttackState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_THROWER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 2, 2, 2, 2, 2, THROWER_FRAME*(1 / 60.0f));
	grid = Grid::GetInstance(BoxCollider(224, 0, 0, 2048));
	
}

ThrowerAttackState::~ThrowerAttackState() {
}

void ThrowerAttackState::ResetState() {

	auto enemy = enemyData->enemy;

	auto playerX = Player::GetInstance()->GetPosition().x;
	auto enemyX = enemy->GetPosition().x;

	enemy->SetVx(0);

	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(13);
	enemy->SetColliderBottom(-22);
	enemy->SetColliderLeft(-12);
	enemy->SetColliderRight(4);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();

	EnemyState::ResetState();
}

void ThrowerAttackState::Update(double dt) {

	m_Animation->Update(dt);
	if (m_Animation->GetPercentTime() < 0.04)
	{

		throwerBullet = new ThrowerBullet();
		throwerBullet->SetActive(true);
		throwerBullet->SetVy(THROWER_BULLET_VELOCITY_Y);
		throwerBullet->SetMoveDirection(enemyData->enemy->GetMoveDirection());
		srand((int)time(0));
		if (enemyData->enemy->GetMoveDirection() == Entity::LeftToRight) {
			throwerBullet->SetPosition(enemyData->enemy->GetPosition().x - 6.5, enemyData->enemy->GetPosition().y + 11); //
			throwerBullet->SetColliderLeft(-5);
			throwerBullet->SetColliderRight(+2);
			throwerBullet->SetVx((1 + rand() % 3) * (THROWER_BULLET_VELOCITY_X));
		}
		else
		{
			throwerBullet->SetPosition(enemyData->enemy->GetPosition().x + 6.5, enemyData->enemy->GetPosition().y + 11); //
			throwerBullet->SetColliderLeft(5);
			throwerBullet->SetColliderRight(-2);
			throwerBullet->SetVx((1 + rand() % 3) * (-THROWER_BULLET_VELOCITY_X));
		}
		throwerBullet->SetAliveState(Entity::Alive);
		unit = new Unit(grid, throwerBullet);
	}
	

	if (m_Animation->GetPercentTime() >= THROWER_ATTACK_PERCENTTIME)
	{
		enemyData->enemy->SetState(EnemyState::Follow);
	}
}

void ThrowerAttackState::Render()
{
	EnemyState::Render();
}

EnemyState::State ThrowerAttackState::GetState()
{
	return Attack;
}
