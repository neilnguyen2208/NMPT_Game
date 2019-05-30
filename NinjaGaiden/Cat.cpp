#include "Cat.h"

Cat::Cat() : Enemy() {
	//Set type
	auto textures = Textures::GetInstance();
		textures->Add(TEX_CAT, "Resources/Sprites/catspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	catFollowState = new CatFollowState(enemyData);
	//Set tag
	tag = Entity::Cat;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_CAT)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;

}

Cat::~Cat() {
}

void Cat::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	auto impactorRect = impactor->GetRect();
	auto myRect = GetRect();
	if (impactor->GetType() == Entity::StaticType) {
		if (side == Entity::Bottom) {
			if ((MyHelper::Distance(myRect.left, impactorRect.left) < ENEMY_OFFSET_BORDER && velocity.x < 0) || (MyHelper::Distance(myRect.right, impactorRect.right) < ENEMY_OFFSET_BORDER && velocity.x > 0)/* || (impactorRect.left > myRect.left && impactorRect.left < myRect.right && velocity.x < 0) || (impactorRect.right > myRect.left && impactorRect.right < myRect.right && velocity.x > 0)*/)
				SetVx(-velocity.x);
			SetVy(CAT_JUMP_VELOCITY);
		}
		//else if ((side == Left && velocity.x < 0) || (side == Right && velocity.x >0))
		//	SetVx(-velocity.x);
	}
}

void Cat::SetColliderTop(int top) {
	collider.top = top;
}

void Cat::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void Cat::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Cat::SetColliderRight(int right) {
	collider.right = right;
}

void Cat::SetState(EnemyState::State state) {
	if (state == EnemyState::Follow)
		enemyData->state = catFollowState;
	if (state == EnemyState::Beaten)
	{
		enemyData->state = enemyBeatenState;
	}

	enemyData->state->ResetState();
}

BoxCollider Cat::GetCollider() {
	return collider;
}

void Cat::Spawn() {
	//Set state first
	SetState(EnemyState::Follow);
	Enemy::Spawn();
}
