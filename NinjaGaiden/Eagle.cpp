#include "Eagle.h"

Eagle::Eagle() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EAGLE, "Resources/Sprites/eaglespritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	eagleFollowState = new EagleFollowState(enemyData);
	//Set tag
	tag = Entity::Eagle;
	type = Entity::EnemyType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_EAGLE)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;
}

Eagle::~Eagle() {
}

void Eagle::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	Enemy::OnCollision(impactor, side, collisionTime);
}
void Eagle::Update(double dt) {
	SetMoveDirection(Player::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	Enemy::Update(dt);
	D3DXVECTOR3 target = Player::GetInstance()->GetPosition();
	target.y -= 15;
	D3DXVECTOR2 dir = D3DXVECTOR2(target - position);
	D3DXVec2Normalize(&dir, &dir);

	dir.x *= 5.0f;
	dir.y *= 10.0f;
	AddVelocity(dir);
	velocity.x = MyHelper::Clamp(velocity.x, -180.0f, 180.0f);
	velocity.y = MyHelper::Clamp(velocity.y, -90.0f, 90.0f);
}

void Eagle::SetColliderTop(int top) {
	collider.top = top;
}

void Eagle::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Eagle::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Eagle::SetColliderRight(int right) {
	collider.right = right;
}

void Eagle::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = eagleFollowState;
	if (state == EnemyState::Beaten)
	{
		enemyData->state = enemyBeatenState;
	}	
	enemyData->state->ResetState();
}

BoxCollider Eagle::GetCollider() {
	return collider;
}

void Eagle::Spawn() {
	aliveState = Entity::Alive;
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
