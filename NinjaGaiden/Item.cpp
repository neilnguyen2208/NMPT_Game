#include "Item.h"

Item::Item() {
	type = Entity::ItemType;
	itemData = new ItemData(this);
	auto textures = Textures::GetInstance();
	textures->Add(TEX_HOLDER, "Resources/Sprites/holderspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	textures->Add(TEX_ITEM, "Resources/Sprites/itemspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
}

Item::~Item() {
}

void Item::Update(double dt) {
	if (isActive);
	itemData->state->Update(dt);
}

void Item::Render() {
	itemData->state->Render();
}

BoxCollider Item::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}

BoxCollider Item::GetSpawnRect() {
	return spawnBox;
}

void Item::SetActive(bool active) {
	if (active)
		Spawn();
	else
		MakeInactive();
}

void Item::SetSpawnBox(BoxCollider box) {
	spawnBox = box;
	spawnPosition.x = (box.right + box.left) / 2;
	spawnPosition.y = (box.top + box.bottom) / 2;
	collider.top = box.top - spawnPosition.y;
	collider.bottom = -collider.bottom;
	collider.right = box.right - spawnPosition.x;
	collider.left = -collider.right;
	MakeInactive();
}

float Item::GetWidth() {
	return collider.right - collider.left;
}

float Item::GetHeight() {
	return collider.top - collider.bottom;
}

void Item::OnCollision(Entity * impactor, SideCollision side, float collisionTime) {
}

void Item::MakeInactive() {
	isActive = false;
	position = spawnPosition;
}

void Item::Spawn() {
	isActive = true;
}
