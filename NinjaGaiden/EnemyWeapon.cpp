#include "EnemyWeapon.h"
#include"GameConfig.h"
#include"Debug.h"

EnemyWeapon::EnemyWeapon()
{
	type = Entity::EnemyWeaponType;
	direction = Entity::LeftToRight;
	isActive = false;
	auto textures = Textures::GetInstance();
	textures->Add(TEX_EXPLODE_WEAPON, "Resources/Sprites/ExplodeWeapon.png", D3DCOLOR_XRGB(254, 163, 176));
	
	//Set tag
	D3DSURFACE_DESC desc;
	textures->Get(TEX_EXPLODE_WEAPON)->GetLevelDesc(0, &desc);
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_EXPLODE_WEAPON);
	ExplodeWidth = desc.Width / 3;
	ExplodeHeight = desc.Height;

	m_AnimationExplode = new Animation();
	m_AnimationExplode->AddFrames(texture, 1, 3, 0.05f);

	SetAliveState(Entity::Alive);

	camera = Camera::GetInstance();

}

bool EnemyWeapon::IsActive()
{
	return isActive;
}

void EnemyWeapon::Update(double dt)
{
	BoxCollider r2 = camera->GetRect();
	if ((this->GetRect().bottom > r2.top ||this->GetRect().top < r2.bottom || this->GetRect().left > r2.right || this->GetRect().right < r2.left))//ko overlap
	{
		SetAliveState(Entity::Remove);
		MakeInactive();
	}
	if (GetAliveState() == Entity::Die)
	{
		if (!m_AnimationExplode->IsLastFrame(dt))
		{
			velocity.x = 0;
			velocity.y = 0;
			m_AnimationExplode->Update(dt);
		}
		if (m_AnimationExplode->IsLastFrame(dt)){
			m_AnimationExplode->ResetAnimation();
			SetAliveState(Entity::Remove);
			MakeInactive();
		}
	}
	else
	{
		m_Animation->Update(dt);
		/*if (m_Animation->IsLastFrame(dt)) {
			m_Animation->ResetAnimation();
		}*/
	}
	Entity::Update(dt);
}

void EnemyWeapon::Render() {
	if (GetAliveState()==Entity::Die&&IsActive()==true)
	{
		m_AnimationExplode->Render(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), direction == Entity::EntityDirection::RightToLeft);
	}
	else
	{
		m_Animation->Render(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), direction == Entity::EntityDirection::RightToLeft);
	}
}

void EnemyWeapon::SetColliderTop(int top) {
	collider.top = top;
}

void EnemyWeapon::SetColliderLeft(int left) {
	collider.left = left;
}

void EnemyWeapon::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void EnemyWeapon::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider EnemyWeapon::GetCollider() {
	return collider;
}

BoxCollider EnemyWeapon::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;

	if (direction == Entity::LeftToRight) {
		r.left = position.x + collider.left;
		r.right = position.x + collider.right;
	}
	else {
		r.left = position.x - collider.right;
		r.right = position.x - collider.left;
	}
	return r;
}

void EnemyWeapon::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	if (dir == Entity::LeftToRight)
		position.x += offsetScaleX;
	else
		position.x -= offsetScaleX;
}

Entity::EntityDirection EnemyWeapon::GetMoveDirection()
{
	return direction;
}


void EnemyWeapon::OnCollision(Entity* impactor, SideCollision side, float timeCollision)
{
	if (impactor->GetType() == Entity::RyuWeaponType)
	{
		SetAliveState(Entity::Die);
	}
}

void EnemyWeapon::SetRect(BoxCollider box)
{
	collider = box;
}

float EnemyWeapon::GetWidth() {
	return collider.right - collider.left;
}

float EnemyWeapon::GetBigWidth() {
	return width;
}


float EnemyWeapon::GetHeight() {
	return collider.top - collider.bottom;
}

float EnemyWeapon::GetBigHeight() {
	return height;
}

EnemyWeapon::~EnemyWeapon()
{
	delete m_AnimationExplode;
}

void EnemyWeapon::SetActive(bool active) {
	isActive = active;
}

void EnemyWeapon::MakeInactive() {
	isActive = false;
}
