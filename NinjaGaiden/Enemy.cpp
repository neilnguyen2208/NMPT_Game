#include "Enemy.h"
#include "EnemyBeatenState.h"
#include "PlayScene.h"
#include "GameConfig.h"
Enemy::Enemy() : Entity() {

	type = Entity::EnemyType;
	enemyData = new EnemyData();
	enemyData->enemy = this;
	direction = Entity::LeftToRight;
	isActive = false;
	enemyBeatenState = new EnemyBeatenState(enemyData);
}

Enemy::~Enemy() {
}

void Enemy::Update(double dt) {
	if (isActive)
		enemyData->state->Update(dt);
	Entity::Update(dt);
}

void Enemy::Render() {
	if (isActive)
		enemyData->state->Render();
}

BoxCollider Enemy::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;

	if (direction == Entity::LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
	return r;
}

BoxCollider Enemy::GetSpawnRect() {
	return spawnBox;
}

void Enemy::SetActive(bool active) {
	if (active)
		Spawn(); 
	else
		MakeInactive();
}

void Enemy::SetRect(BoxCollider box) {
	collider = box;
}

void Enemy::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.left + box.right) / 2.0f;
	spawnPosition.y = (box.bottom + box.top) / 2.0f;
	spawnDirection = (EntityDirection)direction;
	MakeInactive();
}

void Enemy::SetColliderTop(int top) {
	collider.top = top;
}

void Enemy::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Enemy::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Enemy::SetColliderRight(int right) {
	collider.right = right;
}

void Enemy::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	if (dir == Entity::LeftToRight)
		position.x += offsetScaleX;
	else
		position.x -= offsetScaleX;
}

void Enemy::SetState(EnemyState::State state) {
}

float Enemy::GetWidth() {
	return collider.right - collider.left;
}

float Enemy::GetBigWidth() {
	return width;
}

float Enemy::GetHeight() {
	return collider.top - collider.bottom;
}

float Enemy::GetBigHeight() {
	return height;
}

BoxCollider Enemy::GetCollider() {
	return collider;
}

void Enemy::OnCollision(Entity * impactor, SideCollision side, float collisionTime) {
	auto impactorRect = impactor->GetRect();
	auto myRect = GetRect();
	if (impactor->GetType() == Entity::StaticType&&enemyData->enemy->GetTag()!=Entity::Eagle) {
		if (side == Entity::Bottom) {
			if ((MyHelper::Distance(myRect.left, impactorRect.left) < ENEMY_OFFSET_BORDER && velocity.x < 0) || (MyHelper::Distance(myRect.right, impactorRect.right) < ENEMY_OFFSET_BORDER && velocity.x > 0) || (impactorRect.left > myRect.left && impactorRect.left < myRect.right && velocity.x < 0) || (impactorRect.right > myRect.left && impactorRect.right < myRect.right && velocity.x > 0))
			{
				if (enemyData->enemy->GetTag() != Entity::Cat && enemyData->enemy->GetTag() != Entity::Runner)
					SetVx(-velocity.x);
			}
			SetVy(0);
		}
	}
	if (impactor->GetType() == Entity::RyuWeaponType)
	{
		enemyData->enemy->SetState(EnemyState::Beaten);
	}
}

void Enemy::MakeInactive() {
	isActive = false;
	position = spawnPosition;
	direction = spawnDirection;
	SetColliderTop((spawnBox.top - spawnBox.bottom) / 2.0f);
	SetColliderBottom(-collider.top);
	SetColliderLeft((spawnBox.left - spawnBox.right) / 2.0f);
}

void Enemy::Spawn() {
	isActive = true;
	position.x = spawnBox.left + width / 2.0f;
	position.y = spawnBox.bottom + height / 2.0f;
}

Entity::EntityDirection Enemy::GetSpawnDirection() {
	return spawnDirection;
}

