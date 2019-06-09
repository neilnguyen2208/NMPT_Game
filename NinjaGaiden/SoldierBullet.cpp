#include "SoldierBullet.h"
#include"GameConfig.h"
SoldierBullet::SoldierBullet()
{
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_SOLDIER_BULLET, "Resources/Sprites/SoldierBullet.png", D3DCOLOR_XRGB(254, 163, 176));

	//Set tag
	type = Entity::EnemyWeaponType;
	tag = Entity::SoldierBullet;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_SOLDIER_BULLET)->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_SOLDIER_BULLET);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 1, SOLDIER_BULLET_FRAME*(1.0/60));

	SetVy(SOLDIER_BULLET_VELOCITY_Y);
	SetColliderLeft(-4);
	SetColliderRight(+4);
	SetColliderTop(+2);
	SetColliderBottom(-2);

}

void SoldierBullet::OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime)
{
	EnemyWeapon::OnCollision(impactor, side, collisionTime);
}

void SoldierBullet::Render()
{
	EnemyWeapon::Render();
}

SoldierBullet::~SoldierBullet()
{
	delete m_Animation;
}

void SoldierBullet::Update(double dt)
{
	EnemyWeapon::Update(dt);
}

