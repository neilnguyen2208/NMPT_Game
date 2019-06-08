#include "CannonerBullet.h"
#include"GameConfig.h"
CannonerBullet::CannonerBullet()
{
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_CANNONER_BULLET, "Resources/Sprites/CannonerBullet.png", D3DCOLOR_XRGB(254, 163, 176));

	//Set tag
	type = Entity::EnemyWeaponType;
	tag = Entity::CannonerBullet;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_CANNONER_BULLET)->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_CANNONER_BULLET);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 1,CANNONER_BULLET_FRAME*(1.0/60));

	SetVy(CANNONER_BULLET_VELOCITY_Y);
	SetColliderLeft(-4);
	SetColliderRight(+4);
	SetColliderTop(+2);
	SetColliderBottom(-2);

}

void CannonerBullet::OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime)
{
	EnemyWeapon::OnCollision(impactor, side, collisionTime);
}

void CannonerBullet::Render()
{
	EnemyWeapon::Render();
}

CannonerBullet::~CannonerBullet()
{
	delete m_Animation;
}

void CannonerBullet::Update(double dt)
{
	EnemyWeapon::Update(dt);
}

