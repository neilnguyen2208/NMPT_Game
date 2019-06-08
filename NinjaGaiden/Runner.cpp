#include "Runner.h"

Runner::Runner() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_RUNNER, "Resources/Sprites/Runner.png", D3DCOLOR_XRGB(254, 163, 176));
	runnerFollowState = new RunnerFollowState(enemyData);
	//Set tag
	tag = Entity::Runner;
	type = Entity::EnemyType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_RUNNER)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;
}

Runner::~Runner() {
}

void Runner::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
}

void Runner::SetColliderTop(int top) {
	collider.top = top;
}

void Runner::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Runner::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Runner::SetColliderRight(int right) {
	collider.right = right;
}

void Runner::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = runnerFollowState;
	if (state == EnemyState::Beaten)
	{
		enemyData->state = enemyBeatenState;
	}
	enemyData->state->ResetState();
}

BoxCollider Runner::GetCollider() {
	return collider;
}

void Runner::Spawn() {
	aliveState = Entity::Alive;
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
