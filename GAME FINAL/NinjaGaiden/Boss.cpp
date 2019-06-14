#include "Boss.h"
#include"ExternalDataCollector.h"

Boss::Boss() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BOSS, "Resources/Sprites/BossNew.png", D3DCOLOR_XRGB(254, 163, 176));
	textures->Add(TEX_BOSS_EXPLODE, "Resources/Sprites/BossExplodeNew.png", D3DCOLOR_XRGB(254, 163, 176));
	bossFollowState = new BossState(enemyData);
	//Set tag
	tag = Entity::Boss;
	type = Entity::EnemyType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_BOSS)->GetLevelDesc(0, &desc);
	width = desc.Width / 2.0;
	height = desc.Height / 2.0;
	HitPoint = 16;
}

Boss::~Boss() {
}

void Boss::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	
	Enemy::OnCollision(impactor, side, collisionTime);
}

void Boss::Update(double dt) {

	if (ExternalDataCollector::GetInstance()->GetBossHurt())
	{
		ExternalDataCollector::GetInstance()->SetBossHurtTime(ExternalDataCollector::GetInstance()->GetBossHurtTime() + dt);
		if (ExternalDataCollector::GetInstance()->GetBossHurtTime() >= 0.5f)
		{
			ExternalDataCollector::GetInstance()->SetBossHurt(false);
			ExternalDataCollector::GetInstance()->SetBossHurtTime(0);
		}
	}

	SetMoveDirection(Player::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
}

void Boss::SetColliderTop(int top) {
	collider.top = top;
}

void Boss::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Boss::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Boss::SetColliderRight(int right) {
	collider.right = right;
}

void Boss::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = bossFollowState;
	if (state == EnemyState::Beaten)
	{
		enemyData->state = enemyBeatenState;
	}
	enemyData->state->ResetState();
}

BoxCollider Boss::GetCollider() {
	return collider;
}

void Boss::Spawn() {
	aliveState = Entity::Alive;
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
