#include "EnemyWeaponState.h"
#include "EnemyWeapon.h"

EnemyWeaponState::EnemyWeaponState(EnemyWeaponData *data) {
	enemyWeaponData = data;
}

EnemyWeaponState::EnemyWeaponState() {
}

EnemyWeaponState::~EnemyWeaponState() {
}

void EnemyWeaponState::Update(double dt) {
	if (m_Animation)
		m_Animation->Update(dt);
}

void EnemyWeaponState::Render() {
	m_Animation->Render(enemyWeaponData->weapon->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void EnemyWeaponState::OnCollision(Entity * impactor, Entity::SideCollision side) {

}

void EnemyWeaponState::ResetState() {
	m_Animation->ResetAnimation();
}
