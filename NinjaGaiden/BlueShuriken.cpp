#include "BlueShuriken.h"

BlueShuriken::BlueShuriken()
{
	Textures *textures = Textures::GetInstance();
	textures->Add(TEX_BLUE_SHURIKEN_SKILL, "Resources/Sprites/BlueShuriken.png", D3DCOLOR_XRGB(254, 163, 176));
	tag = Entity::BlueShuriken;
	type = Entity::RyuWeaponType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_BLUE_SHURIKEN_SKILL)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;
	
	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_BLUE_SHURIKEN_SKILL);	
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 2, BLUE_SHURIKEN_SKILL_FRAME * (1 / 60.0f));

	SetVy(BLUE_SHURIKEN_VELOCITY_Y);
	SetColliderLeft(-4);
	SetColliderRight(+4);
	SetColliderTop(+4);
	SetColliderBottom(-4);
}

void BlueShuriken::Update(double dt)
{
	RyuWeapon::Update(dt);
}

void BlueShuriken::Render() {
	RyuWeapon::Render();
}

BlueShuriken::~BlueShuriken()
{
}

void BlueShuriken::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime)
{
	if (impactor->GetType() == Entity::EnemyType || impactor->GetType() == Entity::EnemyWeaponType)
	{
		SetAliveState(Entity::Remove);
		SetActive(false);
	}
}

