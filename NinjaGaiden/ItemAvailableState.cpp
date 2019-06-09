#include "ItemAvailableState.h"
#include "Item.h"

ItemAvailableState::ItemAvailableState(ItemData *data) : ItemState(data) {
	this->itemData = data;
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_ITEM);
	m_Animation = new Animation();
	switch (data->item->GetTag()) {
	case Entity::SpiritPoints5:
	{
		m_Animation->AddFramesA(texture, 1, 1, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::SpiritPoints10:
	{
		m_Animation->AddFramesA(texture, 2, 2, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::Scores500:
	{
		m_Animation->AddFramesA(texture, 3, 3, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::Scores1000:
	{
		m_Animation->AddFramesA(texture, 4, 4, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::TimeFreeze:
	{
		m_Animation->AddFramesA(texture, 5, 5, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::Health:
	{
		m_Animation->AddFramesA(texture, 6, 6, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::ThrowingStar:
	{
		m_Animation->AddFramesA(texture, 7, 7, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::WindmillStar:
	{
		m_Animation->AddFramesA(texture, 8, 8, 1, 9, 1, 1.0f);
		break;
	}
	case Entity::Flames:
	{
		m_Animation->AddFramesA(texture, 9, 9, 1, 9, 1, 1.0f);
		break;
	}
	}
}

ItemAvailableState::~ItemAvailableState() {
}

void ItemAvailableState::ResetState() {
	auto item = itemData->item;

}

void ItemAvailableState::Update(double dt) {
	m_Animation->Update(dt);
}
