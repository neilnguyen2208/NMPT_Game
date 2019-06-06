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
	m_Animation->AddFrames(tex, 1, 2, TEX_RED_SHURIKEN_SKILL * (1 / 60.0f));
}

void RedShuriken::SetActive(bool isactive)
{
	this->isActive = isactive;
}

bool RedShuriken::IsActive()
{
	return isActive;
}

void RedShuriken::Update(double dt)
{
	if (isActive)
		m_Animation->Update(dt);
	Entity::Update(dt);
}

void RedShuriken::Render() {
	if (isActive)
		m_Animation->Render();
}


void RedShuriken::SetColliderTop(int top) {
	collider.top = top;
}


void RedShuriken::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void RedShuriken::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void RedShuriken::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider RedShuriken::GetCollider() {
	return collider;
}

BoxCollider RedShuriken::GetRect() {
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

void RedShuriken::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.left + box.right) / 2.0f;
	spawnPosition.y = (box.bottom + box.top) / 2.0f;
	spawnDirection = (EntityDirection)direction;
	MakeInactive();
}

void RedShuriken::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	//if (dir == Entity::LeftToRight)
	//	position.x += offsetScaleX;
	//else
	//	position.x -= offsetScaleX;
}

Entity::EntityDirection RedShuriken::GetMoveDirection()
{
	return direction;
}

void RedShuriken::SetRect(BoxCollider box)
{
	collider = box;
}


float RedShuriken::GetWidth() {
	return collider.right - collider.left;
}

float RedShuriken::GetBigWidth() {
	return width;
}


float RedShuriken::GetHeight() {
	return collider.top - collider.bottom;
}

float RedShuriken::GetBigHeight() {
	return height;
}


BoxCollider RedShuriken::GetSpawnRect() {
	return spawnBox;
}

void RedShuriken::MakeInactive()
{
	isActive = false;
}

void RedShuriken::Spawn() {
	isActive = true;
	position.x = spawnBox.left + width / 2.0f;
	position.y = spawnBox.bottom + height / 2.0f;
}

Entity::EntityDirection RedShuriken::GetSpawnDirection() {
	return spawnDirection;
}


RedShuriken::~RedShuriken()
{
}
