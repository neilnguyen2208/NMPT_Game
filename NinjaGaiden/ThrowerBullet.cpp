#include "ThrowerBullet.h"

ThrowerBullet::ThrowerBullet()
{
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_THROWER_BULLET, "Resources/Sprites/ThrowerBullet.png", D3DCOLOR_XRGB(255, 163, 177));
	//Set tag
	type = Entity::EnemyWeaponType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_THROWER_BULLET)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_THROWER_BULLET);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 2, THROWER_BULLET_FRAME * (1 / 60.0f));
}

void ThrowerBullet::OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime)
{
}

void ThrowerBullet::SetColliderTop(int top) {
	collider.top = top;
}

void ThrowerBullet::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void ThrowerBullet::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void ThrowerBullet::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider ThrowerBullet::GetCollider() {
	return collider;
}

void ThrowerBullet::Spawn() {
	isActive = true;
	position.x = spawnBox.left + width / 2.0f;
	position.y = spawnBox.bottom + height / 2.0f;
}

ThrowerBullet::~ThrowerBullet()
{
}
