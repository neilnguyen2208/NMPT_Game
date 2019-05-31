#include "FlameWheel.h"

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
	m_Animation->AddFrames(tex, 1, 2, TEX_BLUE_SHURIKEN_SKILL * (1 / 60.0f));
}

void BlueShuriken::SetActive(bool isactive)
{
	this->isActive = isactive;
}

bool BlueShuriken::IsActive()
{
	return isActive;
}

void BlueShuriken::Update(double dt)
{
	if (isActive)
		m_Animation->Update(dt);
	Entity::Update(dt);
}

void BlueShuriken::Render() {
	if (isActive)
		m_Animation->Render();
}


void BlueShuriken::SetColliderTop(int top) {
	collider.top = top;
}


void BlueShuriken::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void BlueShuriken::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void BlueShuriken::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider BlueShuriken::GetCollider() {
	return collider;
}

BoxCollider BlueShuriken::GetRect() {
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

void BlueShuriken::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.left + box.right) / 2.0f;
	spawnPosition.y = (box.bottom + box.top) / 2.0f;
	spawnDirection = (EntityDirection)direction;
	MakeInactive();
}

void BlueShuriken::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	//if (dir == Entity::LeftToRight)
	//	position.x += offsetScaleX;
	//else
	//	position.x -= offsetScaleX;
}

Entity::EntityDirection BlueShuriken::GetMoveDirection()
{
	return direction;
}

void BlueShuriken::SetRect(BoxCollider box)
{
	collider = box;
}


float BlueShuriken::GetWidth() {
	return collider.right - collider.left;
}

float BlueShuriken::GetBigWidth() {
	return width;
}


float BlueShuriken::GetHeight() {
	return collider.top - collider.bottom;
}

float BlueShuriken::GetBigHeight() {
	return height;
}


BoxCollider BlueShuriken::GetSpawnRect() {
	return spawnBox;
}

void BlueShuriken::MakeInactive()
{
	isActive = false;
}

void BlueShuriken::Spawn() {
	isActive = true;
	position.x = spawnBox.left + width / 2.0f;
	position.y = spawnBox.bottom + height / 2.0f;
}

Entity::EntityDirection BlueShuriken::GetSpawnDirection() {
	return spawnDirection;
}


BlueShuriken::~BlueShuriken()
{
}
