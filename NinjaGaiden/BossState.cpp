#include "BossState.h"
#include "Enemy.h"
#include"ExternalDataCollector.h"

BossState::BossState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture_1 = textures->Get(TEX_BOSS);
	LPDIRECT3DTEXTURE9 texture_2 = textures->Get(TEX_BOSS_EXPLODE);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture_1, 1, 1, 2, 2, 2, 60.0f * (1 / 60.0f));	
	jump_Animation = new Animation();
	jump_Animation->AddFramesA(texture_1, 2, 2, 1, 2, 2, 60.0f * (1 / 60.0f));
	explode_Animation = new Animation();
	explode_Animation->AddFrames(texture_2, 1, 4, BOSS_EXPLODE_FRAME/60.0f);

	isJump = true;
	isAttack = false;
	turnMove = 0;
	sidePosition = 0;
	
	grid = Grid::GetInstance(BoxCollider(224, 0, 0, 2048));
}

BossState::~BossState() {
}

void BossState::ResetState() {
	auto enemy = enemyData->enemy;
	//Enemy khac nhau co collide khac nhau, initilize class phai chu y 
	enemy->SetColliderTop(27);
	enemy->SetColliderBottom(-27);
	enemy->SetColliderLeft(-19);
	enemy->SetColliderRight(19);
	//
	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();
	enemy->SetVx(0);
	EnemyState::ResetState();
}

void BossState::Update(double dt) {
	//Update Animation
	if (ExternalDataCollector::GetInstance()->GetBossHitPoint() <= 0)
	{
		explode_Animation->Update(dt);
		enemyData->enemy->SetVelocity(D3DXVECTOR2(0, 0));
		CSoundChoose::GetInstance()->StopSound();
		CSoundChoose::GetInstance()->PlaySoundChoose(1);
		return; //return WIN!
	}
	EnemyState::Update(dt);

	//Attack
	if (isAttack) {
		{
			bossBullet_1 = new BossBullet();
			bossBullet_1->SetActive(true);
			if (sidePosition == 1) {
				bossBullet_1->SetPosition(enemyData->enemy->GetPosition().x + 16, enemyData->enemy->GetPosition().y +16); //	
				bossBullet_1->SetVx((BOSS_BULLET_VELOCITY_X));
			}
			else // 8 6
			{
				bossBullet_1->SetPosition(enemyData->enemy->GetPosition().x - 16, enemyData->enemy->GetPosition().y +16); //	
				bossBullet_1->SetVx((-BOSS_BULLET_VELOCITY_X));
			}
			bossBullet_1->SetAliveState(Entity::Alive);
			Unit* unit;
			unit = new Unit(grid, bossBullet_1);
		}
		{
			bossBullet_2 = new BossBullet();
			bossBullet_2->SetActive(true);
			if (sidePosition == 1) {
				bossBullet_2->SetPosition(enemyData->enemy->GetPosition().x + 12, enemyData->enemy->GetPosition().y + 0); //	
				bossBullet_2->SetVx((BOSS_BULLET_VELOCITY_X));
			}
			else // 8 6
			{
				bossBullet_2->SetPosition(enemyData->enemy->GetPosition().x - 12, enemyData->enemy->GetPosition().y + 0); //	
				bossBullet_2->SetVx((-BOSS_BULLET_VELOCITY_X));
			}
			bossBullet_2->SetAliveState(Entity::Alive);
			Unit* unit;
			unit = new Unit(grid, bossBullet_2);
		}
		{
			bossBullet_3 = new BossBullet();
			bossBullet_3->SetActive(true);
			if (sidePosition == 1) {
				bossBullet_3->SetPosition(enemyData->enemy->GetPosition().x + 8, enemyData->enemy->GetPosition().y - 16); //	
				bossBullet_3->SetVx((BOSS_BULLET_VELOCITY_X));
			}
			else // 8 6
			{
				bossBullet_3->SetPosition(enemyData->enemy->GetPosition().x - 8, enemyData->enemy->GetPosition().y - 16); //	
				bossBullet_3->SetVx((-BOSS_BULLET_VELOCITY_X));
			}
			bossBullet_3->SetAliveState(Entity::Alive);
			Unit*unit;
			unit = new Unit(grid, bossBullet_3);
		}
		isAttack = false;
	}

	//On Collision boss // 184 96
	vector<Entity*> staticObjects = Grid::GetInstance(BoxCollider(224, 0, 0, 2048))->staticObject;
	auto side = Entity::SideCollision::NotKnow;
	for (int i = 0; i < staticObjects.size(); i++)
	{
	
		if (staticObjects[i]->GetTag() != Entity::Ground) continue;
		
			float collisionTime = CollisionDetector::SweptAABB(enemyData->enemy, staticObjects[i], side, dt);
			if (collisionTime == 2)
				continue;				
			OnCollision(staticObjects[i], side);
	}

	if (enemyData->enemy->GetPosition().x >= Graphic::GetInstance()->GetBackBufferWidth() / 2)
		sidePosition = 0;
	else
		sidePosition = 1;

}

void BossState::OnCollision(Entity * impactor, Entity::SideCollision side)
{
	enemyData->enemy->SetVelocity(D3DXVECTOR2(0,0));

	if (impactor->GetType() == Entity::StaticType && side == Entity::Bottom)
		CSoundChoose::GetInstance()->PlaySoundChoose(2);

	if (isJump == false)
	{
		if (m_Animation->GetPercentTime() >= 1.1f)
		{
			isJump = true;
			
			enemyData->enemy->SetVy(270);
			if (sidePosition == 0)
			{
				enemyData->enemy->SetVx(-100);
				sidePosition = 1;
			}
			else {
				enemyData->enemy->SetVx(100);
				sidePosition = 0;
			}
			m_Animation->ResetAnimation();
		}
	}
	
	if (isJump)
	{
		if (turnMove == 0)
			turnMove = 1;
		else if (turnMove == 1)
			turnMove = 2;
		else
			if (turnMove == 2)
			{
				srand((int)time(0));
				int i = rand() % 2;
				if (i == 1)
				{
					turnMove = 0; isAttack = true;
				}
				else turnMove = 3;
			}
			else
				if (turnMove == 3)
				{
					turnMove = 0; isAttack = true;
				}
		isJump = false;
	}

}

EnemyState::State BossState::GetState()
{
	return Follow;
}

void BossState::Render()
{
	if (ExternalDataCollector::GetInstance()->GetBossHitPoint() <= 0)
	{
		explode_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::EntityDirection::RightToLeft); return;
	}
	if (isJump)
	{
		jump_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
	}
	else
	{
		EnemyState::Render();
	}
}
