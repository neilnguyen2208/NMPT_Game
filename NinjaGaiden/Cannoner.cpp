#include "Cannoner.h"

Cannoner::Cannoner() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
		textures->Add(TEX_CANNONER, "Resources/Sprites/CannonerBug.png", D3DCOLOR_XRGB(254, 163, 176));
	
	cannonerAttackState = new CannonerAttackState(enemyData);
	//Set tag
	tag = Entity::Cannoner;
	type = Entity::EnemyType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_CANNONER)->GetLevelDesc(0, &desc);
	width = desc.Width / 2.0;
	height = desc.Height / 1.0;
}

Cannoner::~Cannoner() {
}

void Cannoner::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
}

void Cannoner::Update(double dt) {
	SetMoveDirection(Player::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
}

void Cannoner::SetColliderTop(int top) {
	collider.top = top;
}

void Cannoner::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Cannoner::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Cannoner::SetColliderRight(int right) {
	collider.right = right;
}

void Cannoner::SetState(EnemyState::State state) {
	if (state == EnemyState::Attack)
		enemyData->state = cannonerAttackState;
	if (state == EnemyState::Beaten)
	{
		enemyData->state = enemyBeatenState;
	}

	enemyData->state->ResetState();
}

BoxCollider Cannoner::GetCollider() {
	return collider;
}

void Cannoner::Spawn() {
	aliveState = Entity::Alive;
	SetState(EnemyState::Attack);
	Enemy::Spawn();
}
