#include "Soldier.h"

Soldier::Soldier() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SOLDIER, "Resources/Sprites/soldierspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	soldierFollowState = new SoldierFollowState(enemyData);
	soldierAttackState = new SoldierAttackState(enemyData);
	
	//Set tag
	tag = Entity::Soldier;
	type = Entity::EnemyType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_SOLDIER)->GetLevelDesc(0, &desc);
	width = desc.Width / 2.0;
	height = desc.Height / 2.0;
}

Soldier::~Soldier() {
}

void Soldier::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
}

void Soldier::Update(double dt) {
	SetMoveDirection(Player::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
}

void Soldier::SetColliderTop(int top) {
	collider.top = top;
}

void Soldier::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Soldier::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Soldier::SetColliderRight(int right) {
	collider.right = right;
}

void Soldier::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = soldierFollowState;
	if (state == EnemyState::Attack)
		enemyData->state = soldierAttackState;
	if (state == EnemyState::Beaten)
	{
		enemyData->state = enemyBeatenState;
	}
	enemyData->state->ResetState();
}

BoxCollider Soldier::GetCollider() {
	return collider;
}

void Soldier::Spawn() {
	aliveState = Entity::Alive;
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
