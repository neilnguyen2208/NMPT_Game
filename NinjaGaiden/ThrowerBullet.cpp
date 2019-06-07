#include "ThrowerBullet.h"
#include"GameConfig.h"
#include"Debug.h"
#include"Unit.h"
#include"Grid.h"
ThrowerBullet::ThrowerBullet()
{
	//Set type
	auto textures = Textures::GetInstance();
	textures->Add(TEX_THROWER_BULLET, "Resources/Sprites/ThrowerBullet.png", D3DCOLOR_XRGB(254, 163, 176));
	//Set tag
	type = Entity::EnemyWeaponType;
	tag = Entity::ThrowerBullet;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_THROWER_BULLET)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_THROWER_BULLET);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 2, THROWER_BULLET_FRAME*(1.0 / 60));

	SetVy(THROWER_BULLET_VELOCITY_Y);
	SetColliderTop(10);
	SetColliderBottom(-3);
}

void ThrowerBullet::OnCollision(Entity *impactor, Entity::SideCollision side, float collisionTime)
{
	EnemyWeapon::OnCollision(impactor, side, collisionTime);
}

void ThrowerBullet::Render()
{
	EnemyWeapon::Render();
}

ThrowerBullet::~ThrowerBullet()
{
	delete m_Animation;
}

void ThrowerBullet::Update(double dt)
{
	this->AddVy(-GRAVITY-12);
	if (this->GetVelocity().y < 0)
		int x = 0;
	if (this->GetVelocity().y <= THROWER_BULLET_MAX_FALLING_VELOCITY)
		this->SetVy(THROWER_BULLET_MAX_FALLING_VELOCITY);
	EnemyWeapon::Update(dt);		
}

