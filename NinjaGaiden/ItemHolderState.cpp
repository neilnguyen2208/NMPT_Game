#include "ItemHolderState.h"
#include "Item.h"

ItemHolderState::ItemHolderState(ItemData *data) : ItemState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_HOLDER);
	m_Animation = new Animation();
	m_Animation->AddFramesA(texture, 1, 1, 2, 2, 2, HOLDER_FRAME * (1 / 60.0f));
}

ItemHolderState::~ItemHolderState() {
}

void ItemHolderState::ResetState() {

	auto item = itemData->item;
}

void ItemHolderState::Update(double dt) {
	m_Animation->Update(dt);
}
