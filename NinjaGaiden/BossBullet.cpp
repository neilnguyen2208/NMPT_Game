#include "BossBullet.h"
#include"GameConfig.h"
BossBullet::BossBullet()
{
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_BOSS_BULLET, "Resources/Sprites/BossBullet.png", D3DCOLOR_XRGB(254, 163, 176));

	//Set tag
	type = Entity::EnemyWeaponType;
	tag = Entity::BossBullet;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_BOSS_BULLET)->GetLevelDesc(0, &desc);
	width = desc.Width;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_BOSS_BULLET);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 1, BOSS_BULLET_FRAME*(1.0/60));

	SetVy(BOSS_BULLET_VELOCITY_Y);
	SetColliderLeft(-3);
	SetColliderRight(+3);
	SetColliderTop(+3);
	SetColliderBottom(-3);
}

void BossBullet::OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime)
{
	EnemyWeapon::OnCollision(impactor, side, collisionTime);
}

void BossBullet::Render()
{
	EnemyWeapon::Render();
}

BossBullet::~BossBullet()
{
	delete m_Animation;
}

void BossBullet::Update(double dt)
{
	EnemyWeapon::Update(dt);
}

