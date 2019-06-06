#include "FlameWheel.h"

FlameWheel::FlameWheel()
{
	Textures *textures = Textures::GetInstance();
	textures->Add(TEX_FLAME_WHEEL_SKILL, "Resources/Sprites/FlameWheel.png", D3DCOLOR_XRGB(254, 163, 176));
	tag = Entity::FlameWheel;
	type = Entity::RyuWeaponType;
	D3DSURFACE_DESC desc;
	textures->Get(TEX_FLAME_WHEEL_SKILL)->GetLevelDesc(0, &desc);
	width = desc.Width / 2;
	height = desc.Height;
	
	LPDIRECT3DTEXTURE9 tex = textures->Get(TEX_FLAME_WHEEL_SKILL);
	m_Animation = new Animation();
	m_Animation->AddFrames(tex, 1, 2, FLAME_WHEEL_SKILL_FRAME * (1 / 60.0f));
}

void FlameWheel::SetActive(bool isactive)
{
	this->isActive = isactive;
}

bool FlameWheel::IsActive()
{
	return isActive;
}

void FlameWheel::Update(double dt)
{
	if (isActive)
		m_Animation->Update(dt);
	Entity::Update(dt);
}

void FlameWheel::Render() {
	if (isActive)
		m_Animation->Render();
}


void FlameWheel::SetColliderTop(int top) {
	collider.top = top;
}


void FlameWheel::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -collider.left;
}

void FlameWheel::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void FlameWheel::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider FlameWheel::GetCollider() {
	return collider;
}

BoxCollider FlameWheel::GetRect() {
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

void FlameWheel::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.left + box.right) / 2.0f;
	spawnPosition.y = (box.bottom + box.top) / 2.0f;
	spawnDirection = (EntityDirection)direction;
	MakeInactive();
}

void FlameWheel::SetMoveDirection(Entity::EntityDirection dir) {
	if (dir == direction)
		return;
	direction = dir;
	//if (dir == Entity::LeftToRight)
	//	position.x += offsetScaleX;
	//else
	//	position.x -= offsetScaleX;
}

Entity::EntityDirection FlameWheel::GetMoveDirection()
{
	return direction;
}

void FlameWheel::SetRect(BoxCollider box)
{
	collider = box;
}


float FlameWheel::GetWidth() {
	return collider.right - collider.left;
}

float FlameWheel::GetBigWidth() {
	return width;
}


float FlameWheel::GetHeight() {
	return collider.top - collider.bottom;
}

float FlameWheel::GetBigHeight() {
	return height;
}


BoxCollider FlameWheel::GetSpawnRect() {
	return spawnBox;
}

void FlameWheel::MakeInactive()
{
	isActive = false;
}

void FlameWheel::Spawn() {
	isActive = true;
	position.x = spawnBox.left + width / 2.0f;
	position.y = spawnBox.bottom + height / 2.0f;
}

Entity::EntityDirection FlameWheel::GetSpawnDirection() {
	return spawnDirection;
}


FlameWheel::~FlameWheel()
{
}
