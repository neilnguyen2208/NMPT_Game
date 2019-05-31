//#include "RyuWeaponGroup.h"
//
//RyuWeaponGroup::RyuWeaponGroup()
//{
//	type = Entity::RyuWeaponType;
//}
//
//RyuWeaponGroup::~RyuWeaponGroup()
//{
//
//}
//
//void RyuWeaponGroup::SetActive(bool isactive)
//{
//	this->isActive = isactive;
//}
//
//bool RyuWeaponGroup::IsActive()
//{
//	return isActive;
//}
//
//void RyuWeaponGroup::Update(double dt)
//{
//	if (isActive)
//		m_Animation->Update(dt);
//	Entity::Update(dt);
//}
//
//void RyuWeaponGroup::Render() {
//	if (isActive)
//		m_Animation->Render();
//}
//
//
//void RyuWeaponGroup::SetColliderTop(int top) {
//	collider.top = top;
//}
//
//
//void RyuWeaponGroup::SetColliderLeft(int left) {
//	collider.left = left;
//	collider.right = -collider.left;
//}
//
//void RyuWeaponGroup::SetColliderBottom(int bottom) {
//	collider.bottom = bottom;
//}
//
//void RyuWeaponGroup::SetColliderRight(int right) {
//	collider.right = right;
//}
//
//BoxCollider RyuWeaponGroup::GetCollider() {
//	return collider;
//}
//
//BoxCollider RyuWeaponGroup::GetRect() {
//	BoxCollider r;
//	r.top = position.y + collider.top;
//	r.bottom = position.y + collider.bottom;
//
//	if (direction == Entity::LeftToRight) {
//		r.left = position.x + collider.left;
//		r.right = position.x + collider.right;
//	}
//	else {
//		r.left = position.x - collider.right;
//		r.right = position.x - collider.left;
//	}
//	return r;
//}
//
//void RyuWeaponGroup::SetSpawnBox(BoxCollider box, int direction) {
//	spawnBox = box;
//	spawnPosition.x = (box.left + box.right) / 2.0f;
//	spawnPosition.y = (box.bottom + box.top) / 2.0f;
//	spawnDirection = (EntityDirection)direction;
//	MakeInactive();
//}
//
//void RyuWeaponGroup::SetMoveDirection(Entity::EntityDirection dir) {
//	if (dir == direction)
//		return;
//	direction = dir;
//	//if (dir == Entity::LeftToRight)
//	//	position.x += offsetScaleX;
//	//else
//	//	position.x -= offsetScaleX;
//}
//
//Entity::EntityDirection RyuWeaponGroup::GetMoveDirection()
//{
//	return direction;
//}
//
//void RyuWeaponGroup::SetRect(BoxCollider box)
//{
//	collider = box;
//}
//
//
//float RyuWeaponGroup::GetWidth() {
//	return collider.right - collider.left;
//}
//
//float RyuWeaponGroup::GetBigWidth() {
//	return width;
//}
//
//
//float RyuWeaponGroup::GetHeight() {
//	return collider.top - collider.bottom;
//}
//
//float RyuWeaponGroup::GetBigHeight() {
//	return height;
//}
//
//
//BoxCollider RyuWeaponGroup::GetSpawnRect() {
//	return spawnBox;
//}
//
//void RyuWeaponGroup::MakeInactive()
//{
//	isActive = false;
//}
//
//void RyuWeaponGroup::Spawn() {
//	isActive = true;
//	position.x = spawnBox.left + width / 2.0f;
//	position.y = spawnBox.bottom + height / 2.0f;
//}
//
//Entity::EntityDirection RyuWeaponGroup::GetSpawnDirection() {
//	return spawnDirection;
//}
