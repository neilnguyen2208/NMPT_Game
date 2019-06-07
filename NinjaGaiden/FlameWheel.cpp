#include "FlameWheel.h"

FlameWheel::FlameWheel()
{
	Textures *textures = Textures::GetInstance();
	textures->Add(TEX_FLAME_WHEEL_SKILL, "Resources/Sprites/FlameWheel.png", D3DCOLOR_XRGB(254, 163, 176));
	tag = Entity::FlameWheel;
	type = Entity::RyuWeaponType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_FLAME_WHEEL_SKILL)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_FLAME_WHEEL_SKILL);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 4, FLAME_WHEEL_SKILL_FRAME * (1 / 60.0f));

	SetColliderLeft(-18);
	SetColliderRight(18);
	SetColliderTop(16);
	SetColliderBottom(-16);
}

void FlameWheel::Update(double dt)
{
	RyuWeapon::Update(dt);
}

void FlameWheel::Render() {
	RyuWeapon::Render();
}

FlameWheel::~FlameWheel()
{
}

void FlameWheel::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime)
{
	RyuWeapon::OnCollision(impactor, side, collisionTime);
}

