#include "RedShuriken.h"

RedShuriken::RedShuriken()
{
	Textures *textures = Textures::GetInstance();
	textures->Add(TEX_RED_SHURIKEN_SKILL, "Resources/Sprites/RedShuriken.png", D3DCOLOR_XRGB(254, 163, 176));
	tag = Entity::RedShuriken;
	type = Entity::RyuWeaponType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_RED_SHURIKEN_SKILL)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;

	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_RED_SHURIKEN_SKILL);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 2, RED_SHURIKEN_SKILL_FRAME * (1 / 60.0f));

	SetVy(RED_SHURIKEN_VELOCITY_Y);
	SetColliderLeft(-4);
	SetColliderRight(+4);
	SetColliderTop(+4);
	SetColliderBottom(-4);
}

void RedShuriken::Update(double dt)
{
	SetMoveDirection(Player::GetInstance()->GetPosition().x < position.x ? Entity::RightToLeft : Entity::LeftToRight);
	RyuWeapon::Update(dt);
	target = Player::GetInstance()->GetPosition();

	D3DXVECTOR2 distance = D3DXVECTOR2(target - position);
	D3DXVec2Normalize(&distance, &distance);

	accelerateX = distance.x * 10.0f;
	accelerateY = distance.y * 3.0f;

	velocity.x += accelerateX;
	velocity.y += accelerateY;
}

void RedShuriken::Render() {
	RyuWeapon::Render();
}

RedShuriken::~RedShuriken()
{
}

void RedShuriken::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime)
{
	if (impactor->GetType() == Entity::PlayerType)
	{
		SetAliveState(Entity::Remove);
		SetActive(false);
	}
}

void RedShuriken::SetAccelerate(float x, float y)
{
	accelerateX = x;
	accelerateY = y;
}

void RedShuriken::SetAccelerateX(float x)
{
	accelerateX = x;
}

void RedShuriken::SetAccelerateY(float y)
{
	accelerateY = y;
}

void RedShuriken::SetTarget(D3DXVECTOR3 target)
{
	this->target.x = target.x;
	this->target.y = target.y;
}
