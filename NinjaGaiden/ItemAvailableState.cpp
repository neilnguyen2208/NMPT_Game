#include "ItemAvailableState.h"
#include "Item.h"

ItemAvailableState::ItemAvailableState(ItemData *data) : ItemState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_ITEM);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 1, 9, 1, 1.0f);
}

ItemAvailableState::~ItemAvailableState() {
}

void ItemAvailableState::ResetState() {

	auto item = itemData->item;

}

void ItemAvailableState::Update(double dt) {
	m_Animation->Update(dt);
}
