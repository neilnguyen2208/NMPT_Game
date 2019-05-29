#include "EnemyBeatenState.h"
#include"Debug.h"


EnemyBeatenState::EnemyBeatenState(EnemyData* data)
{
	this->enemyData = data;
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EXPLODE, "Resources/Sprites/EnemyBeatenSprite.png", D3DCOLOR_XRGB(254, 163, 176));
	m_Animation = new Animation();
	m_Animation->AddFramesA(textures->Get(TEX_EXPLODE), 1, 1, 3, 1, 3, 0.05f);
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
	enemyData->enemy->SetVx(0);
	enemyData->enemy->SetVy(0);

	DebugOut(L"Enemy has been defeated");
	EnemyState::ResetState();
}
