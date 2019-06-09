#include "ItemState.h"
#include "Item.h"

ItemState::ItemState(ItemData *data) {
	itemData = data;
}

ItemState::ItemState() {
}

ItemState::~ItemState() {
}

void ItemState::Update(double dt) {
	if (m_Animation)
		m_Animation->Update(dt);
}

void ItemState::Render() {
	m_Animation->Render(itemData->item->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), false);
}

void ItemState::OnCollision(Entity * impactor, Entity::SideCollision side) {

}

int ItemState::GetAnimationHeight() {
	return m_Animation->GetHeightCurrentFrame();
}

int ItemState::GetAnimationWidth() {
	return m_Animation->GetWidthCurrentFrame();
}

void ItemState::ResetState() {
	m_Animation->ResetAnimation();
}
