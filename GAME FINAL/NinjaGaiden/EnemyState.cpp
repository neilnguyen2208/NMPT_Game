#include "EnemyState.h"
#include "Enemy.h"

EnemyState::EnemyState(EnemyData *data) {
	enemyData = data;
}

EnemyState::EnemyState() {
}

EnemyState::~EnemyState() {
}

void EnemyState::Update(double dt) {
	m_Animation->Update(dt);
}

void EnemyState::Render() {
	m_Animation->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
}

void EnemyState::OnCollision(Entity * impactor, Entity::SideCollision side) {

}

void EnemyState::ResetState() {
	m_Animation->ResetAnimation();
}

EnemyState::State EnemyState::GetState()
{
	return Follow;
}
