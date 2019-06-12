#include "Entity.h"

int Entity::currentID = 0;

void Entity::OnSetPosition(D3DXVECTOR3 pos) {
}

Entity::Entity() {
	tag = None;
	id = ++currentID;
	isStatic = false;
}

BoxCollider Entity::GetRect() {
	BoxCollider r;
	r.left = position.x - width / 2;
	r.top = position.y + height / 2;
	r.right = r.left + width;
	r.bottom = r.top - height;
	return r;
}

void Entity::SetActive(bool active) {
	isActive = active;
}

bool Entity::IsActive() {
	return isActive;
}

Entity::EntityTag Entity::GetTag() {
	return tag;
}

void Entity::SetTag(EntityTag tag) {
	this->tag = tag;
}

Entity::EntityType Entity::GetType() {
	return type;
}

void Entity::SetType(EntityType type) {
	this->type = type;
}

Entity::EntityAliveState Entity::GetAliveState()
{
	return this->aliveState;
}

void Entity::SetAliveState(EntityAliveState alivestate)
{
	this->aliveState = alivestate;
}

void Entity::SetStatic(bool flag) {
	isStatic = flag;
	velocity = D3DXVECTOR2(0, 0);
}


void Entity::SetPosition(float x, float y) {
	SetPosition(D3DXVECTOR3(x, y, 0));
}

void Entity::SetPosition(D3DXVECTOR2 pos) {
	SetPosition(D3DXVECTOR3(pos));
}

void Entity::SetPosition(D3DXVECTOR3 pos) {
	position = pos;
	OnSetPosition(position);
}

void Entity::AddPosition(D3DXVECTOR3 pos) {
	SetPosition(pos + position);
}

void Entity::AddPosition(D3DXVECTOR2 pos) {
	AddPosition(D3DXVECTOR3(pos));
}

void Entity::AddPosition(float x, float y) {
	AddPosition(D3DXVECTOR3(x, y, 0));
}

D3DXVECTOR3 Entity::GetPosition() {
	return position;
}

Entity::EntityDirection Entity::GetMoveDirection() {
	return direction;
}

void Entity::SetMoveDirection(EntityDirection direction) {
	this->direction = direction;
}

void Entity::SetWidth(int width) {
	this->width = width;
}

float Entity::GetWidth() {
	return width;
}

void Entity::SetHeight(int height) {
	this->height = height;
}

float Entity::GetHeight() {
	return height;
}

void Entity::SetVelocity(D3DXVECTOR2 vel) {
	if (vel.x > 0)
		direction = LeftToRight;
	else
		if (vel.x < 0)
			direction = RightToLeft;
	velocity = vel;
}

D3DXVECTOR2 Entity::GetVelocity() {
	return velocity;
}

float Entity::GetVx(){
	return velocity.x;
}

void Entity::SetVx(float vx) {
	if (vx > 0)
		SetMoveDirection(LeftToRight);
	else
		if (vx < 0)
			SetMoveDirection(RightToLeft);
	this->velocity.x = vx;
}

void Entity::AddVx(float vx) {
	this->velocity.x += vx;
}

float Entity::GetVy() {
	return velocity.y;
}

void Entity::SetVy(float vy) {
	this->velocity.y = vy;
}

void Entity::AddVy(float vy) {
	this->velocity.y += vy;
}

void Entity::AddVelocity(D3DXVECTOR2 vel) {
	velocity.x += vel.x;
	velocity.y += vel.y;
}

int Entity::GetID() {
	return id;
}

void Entity::Update(double dt) {
	position.x += velocity.x * dt;
	position.y += velocity.y * dt;
}

void Entity::Render() {
}

void Entity::OnCollision(Entity * impactor, SideCollision side, float collisionTime) {
	//velocity = D3DXVECTOR2(0, 0);
}

void Entity::MakeInactive()
{
}

void Entity::SetStatusItem(StatusItem status)
{
	this->status = status;
}

Entity::StatusItem Entity::GetStatusItem()
{
	return status;
}

Entity::~Entity()
{

}