#include "Item.h"
#include "ItemAvailableState.h"
#include "ItemHolderState.h"

Item::Item(Entity::EntityTag tagItem) : Entity() {

	type = Entity::ItemType;
	SetTag(tagItem);
	auto textures = Textures::GetInstance();
	textures->Add(TEX_HOLDER, "Resources/Sprites/holderspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));
	textures->Add(TEX_ITEM, "Resources/Sprites/itemspritesheet.png", D3DCOLOR_XRGB(255, 163, 177));

	itemData = new ItemData();
	itemData->item = this;

	itemAvailableState = new ItemAvailableState(itemData);
	itemHolderState = new ItemHolderState(itemData);

	SetState(ItemState::Unavailable);
	SetType(Entity::EntityType::ItemType);
	SetStatusItem(Entity::UnavailableItem);
	SetMoveDirection(Entity::RightToLeft);

}

Item::~Item() {
}

void Item::Update(double dt) {
	if (isActive)
		itemData->state->Update(dt);
	if (itemData->item->GetStatusItem() == Entity::AvailableItem)
		if (timelimit < ITEM_TIME_LIMIT)
		{
			Entity::Update(dt);
			timelimit += dt * 100;
		}
		else MakeInactive();

}

void Item::Render() {
	itemData->state->Render();
}

void Item::SetState(ItemState::State name)
{
	switch (name) {
	case ItemState::Unavailable:
		itemData->state = itemHolderState;
		break;
	case ItemState::Available:
		itemData->state = itemAvailableState;
		break;
	}

	itemData->state->ResetState();
}

BoxCollider Item::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.bottom = position.y + collider.bottom;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	return r;
}


void Item::SetMoveDirection(Entity::EntityDirection dir)
{
	if (dir == direction)
		return;
	direction = dir;
}

void Item::SetActive(bool active) {
	if (active)
		isActive = true;
	else
		MakeInactive();
}

void Item::SetSpawnBox(BoxCollider box, int direction) {
	spawnBox = box;
	spawnPosition.x = (box.right + box.left) / 2;
	spawnPosition.y = (box.top + box.bottom) / 2;
	collider.top = 8;
	collider.bottom = -8;
	collider.right = 8;
	collider.left = -8;
	MakeInactive();
}

float Item::GetWidth() {
	return collider.right - collider.left;
}

float Item::GetHeight() {
	return collider.top - collider.bottom;
}

void Item::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	if (impactor->GetType() == Entity::RyuWeaponType && itemData->item->GetStatusItem() == Entity::UnavailableItem)
	{
		itemData->item->SetState(ItemState::Available);
		SetStatusItem(Entity::AvailableItem);
		SetVy(-ITEM_VY);
	}
	if (impactor->GetType() == Entity::StaticType && side == Entity::Bottom)
	{
		SetVy(0);
	}
}


void Item::MakeInactive() {
	isActive = false;
	position = spawnPosition;
}


void Item::SetColliderTop(int top)
{
	collider.top = top;
}

void Item::SetColliderLeft(int left)
{
	collider.left = left;
	collider.right = -collider.left;
}

void Item::SetColliderBottom(int bottom)
{
	collider.bottom = bottom;
}

void Item::SetColliderRight(int right)
{
	collider.right = right;
}

