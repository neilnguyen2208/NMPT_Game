#include "EnemyWeapon.h"

EnemyWeapon::EnemyWeapon()
{
}

void EnemyWeapon::SetActive(bool isactive)
{
	this->isActive = isactive;
}

bool EnemyWeapon::IsActive()
{
	return isActive;
}

void EnemyWeapon::Update(double dt)
{
	if (isActive)
		m_Animation->Update(dt);
	Entity::Update(dt);
}

void EnemyWeapon::Render() {
	if (isActive)
		m_Animation->Render();
}


void EnemyWeapon::SetColliderTop(int top) {
	collider.top = top;
}


void EnemyWeapon::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
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

void EnemyWeapon::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.left + box.right) / 2.0f;
	spawnPosition.y = (box.bottom + box.top) / 2.0f;
	spawnDirection = (EntityDirection)direction;
	MakeInactive();
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


BoxCollider EnemyWeapon::GetSpawnRect() {
	return spawnBox;
}

void EnemyWeapon::MakeInactive()
{
	isActive = false;
}

void EnemyWeapon::Spawn() {
	isActive = true;
	position.x = spawnBox.left + width / 2.0f;
	position.y = spawnBox.bottom + height / 2.0f;
}

Entity::EntityDirection EnemyWeapon::GetSpawnDirection() {
	return spawnDirection;
}


EnemyWeapon::~EnemyWeapon()
{
}
