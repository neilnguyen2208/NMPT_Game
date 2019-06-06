#include "EnemyBeatenState.h"
#include"Debug.h"


EnemyBeatenState::EnemyBeatenState(EnemyData* data)
{
	this->enemyData = data;
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EXPLODE_ENEMY, "Resources/Sprites/ExplodeEnemy.png", D3DCOLOR_XRGB(254, 163, 176));
	m_Animation = new Animation();
	m_Animation->AddFramesA(textures->Get(TEX_EXPLODE_ENEMY), 1, 1, 3, 1, 3, 0.05f);
}

EnemyBeatenState::~EnemyBeatenState()
{
}

void EnemyBeatenState::Render()
{
	m_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void EnemyBeatenState::OnCollision(Entity* impactor, Entity::SideCollision side)
{

}

EnemyState::State EnemyBeatenState::GetState()
{
	return EnemyState::Beaten;
}

void EnemyBeatenState::Update(double dt)
{
	m_Animation->Update(dt);
	if (m_Animation->IsLastFrame(dt) == true)
	{
		enemyData->enemy->MakeInactive();
	}
}

void EnemyBeatenState::ResetState()
{
	if (enemyData->enemy->GetType() == Entity::EnemyType&&enemyData->enemy->GetTag() != Entity::Boss)
	{
		enemyData->enemy->SetAliveState(Entity::Die);
		enemyData->enemy->SetVx(0);
		enemyData->enemy->SetVy(0);
		enemyData->enemy->SetColliderTop(0);
		enemyData->enemy->SetColliderLeft(0);
		enemyData->enemy->SetColliderLeft(0);
		enemyData->enemy->SetColliderRight(0);
	}
	if (enemyData->enemy->GetType() == Entity::EnemyType&&enemyData->enemy->GetTag() == Entity::Boss)
	{
		enemyData->enemy->SetAliveState(Entity::Beaten);
	}
	EnemyState::ResetState();
}
