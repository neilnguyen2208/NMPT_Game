#include "Thrower.h"

Thrower::Thrower() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
		textures->Add(TEX_THROWER, "Resources/Sprites/throwerspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	throwerFollowState = new ThrowerFollowState(enemyData);
	throwerAttackState = new ThrowerAttackState(enemyData);
	//Set tag
	tag = Entity::Thrower;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_THROWER)->GetLevelDesc(0, &desc);

	width = desc.Width / 2.0;
	height = desc.Height / 2.0;
}

Thrower::~Thrower() {
}

void Thrower::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
}

void Thrower::SetVelocity(D3DXVECTOR2 vel){
	velocity = vel;
}

void Thrower::SetVx(float vx) {
	velocity.x = vx;
}

void Thrower::Update(double dt) {
	SetMoveDirection(Player::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
}

void Thrower::SetColliderTop(int top) {
	collider.top = top;
}

void Thrower::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Thrower::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Thrower::SetColliderRight(int right) {
	collider.right = right;
}

void Thrower::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = throwerFollowState;
	else
		enemyData->state = throwerAttackState;
	enemyData->state->ResetState();
}

BoxCollider Thrower::GetCollider() {
	return collider;
}

void Thrower::Spawn() {
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
