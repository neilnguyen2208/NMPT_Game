#include "RyuWeapon.h"
#include"GameConfig.h"


RyuWeapon::RyuWeapon()
{
	type = Entity::RyuWeaponType;
	isActive = false;

	//Set tag
	SetAliveState(Entity::Alive);
	camera = Camera::GetInstance();

}

bool RyuWeapon::IsActive()
{
	return isActive;
}

void RyuWeapon::Update(double dt)
{
	BoxCollider r2 = camera->GetRect();
	if ((this->GetRect().bottom > r2.top || this->GetRect().top < r2.bottom || this->GetRect().left > r2.right || this->GetRect().right < r2.left))//ko overlap
	{
		SetAliveState(Entity::Remove);
		MakeInactive();
		return;
	}
	else
		if (GetAliveState() == Entity::Remove)
			return;
	m_Animation->Update(dt);
	Entity::Update(dt);
}

void RyuWeapon::Render() {
	if (IsActive())
	{
		m_Animation->Render(position, BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), direction == Entity::EntityDirection::RightToLeft);
	}
}

void RyuWeapon::SetColliderTop(int top) {
	collider.top = top;
}

void RyuWeapon::SetColliderLeft(int left) {
	collider.left = left;
}

void RyuWeapon::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void RyuWeapon::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider RyuWeapon::GetCollider() {
	return collider;
}

BoxCollider RyuWeapon::GetRect() {
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

void RyuWeapon::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	if (dir == Entity::LeftToRight)
		position.x += offsetScaleX;
	else
		position.x -= offsetScaleX;
}

Entity::EntityDirection RyuWeapon::GetMoveDirection()
{
	if (velocity.x > 0)
		return LeftToRight;
	if (velocity.x < 0)
		return RightToLeft;
	return direction;
}


void RyuWeapon::OnCollision(Entity* impactor, SideCollision side, float timeCollision)
{
}

void RyuWeapon::SetRect(BoxCollider box)
{
	collider = box;
}

float RyuWeapon::GetWidth() {
	return collider.right - collider.left;
}

float RyuWeapon::GetBigWidth() {
	return width;
}


float RyuWeapon::GetHeight() {
	return collider.top - collider.bottom;
}

float RyuWeapon::GetBigHeight() {
	return height;
}

RyuWeapon::~RyuWeapon()
{
}

void RyuWeapon::SetActive(bool active) {
	isActive = active;
}

void RyuWeapon::MakeInactive() {
	isActive = false;
}
