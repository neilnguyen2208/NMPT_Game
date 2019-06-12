#include "Sprites.h"
#include "Camera.h"
//Sprite

Sprite::Sprite(BoxCollider r, LPDIRECT3DTEXTURE9 tex) {
	texture = tex;
	if (IsRect(r)) {
		width = r.right - r.left;
		height = r.bottom - r.top;
		rect = r;
	}
	else {
		D3DSURFACE_DESC desc;
		texture->GetLevelDesc(0, &desc);
		height = desc.Height;
		width = desc.Width;
		rect = BoxCollider(0, 0, height, width);
	}

	m_Position = D3DXVECTOR3(0, 0, 0);
	m_Translation = D3DXVECTOR2(0, 0);

	spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
}

int Sprite::GetWidth() {
	return width;
}

int Sprite::GetHeight() {
	return height;
}

void Sprite::SetWidth(int width) {
	this->width = width;
}

void Sprite::SetHeight(int height) {
	this->height = height;
}

bool Sprite::IsRect(BoxCollider r) {
	if (r.top == r.bottom)
		return false;
	if (r.left == r.right)
		return false;
	return true;
}

void Sprite::Draw(D3DXVECTOR3 position, BoxCollider r, D3DXCOLOR colorKey, bool reverse) {
	auto cam = Camera::GetInstance()->GetRect();
	
	//phng: Doc them cai slide thay Kha de hieu ro hon ve matrix nay nghe
	if (!IsRect(cam))
		return;

	D3DXVECTOR3 inPosition = m_Position;
	BoxCollider inSourceRect = rect;

	if (position != D3DXVECTOR3())
		inPosition = position;

	if (IsRect(r))
		inSourceRect= r;

	D3DXMATRIX m_Maxtrix;
	D3DXMatrixIdentity(&m_Maxtrix);
	m_Maxtrix._22 = -1;
	m_Maxtrix._41 = -cam.left;
	m_Maxtrix._42 = cam.top;
	
	D3DXVECTOR3 center = D3DXVECTOR3(width / 2, height / 2, 0);
	
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &inPosition, &m_Maxtrix);
	D3DXVECTOR3 p(vp_pos.x, vp_pos.y, 0);
	p.x = (int)p.x;
	p.y = (int)p.y;

	D3DXMATRIX oldMatrix;
	spriteHandler->GetTransform(&oldMatrix);

	if (reverse) {
		D3DXMatrixIdentity(&m_Maxtrix);
		auto scalingScenter = D3DXVECTOR2(p.x, p.y);
		auto inCcale = D3DXVECTOR2(-1, 1);
		auto inRotationCenter = D3DXVECTOR2(0, 0);
		auto inRotation = 0;
		auto inTranslation = D3DXVECTOR2(0, 0);
		D3DXMatrixTransformation2D(&m_Maxtrix, &scalingScenter, 0, &inCcale, &inRotationCenter,
			inRotation, &inTranslation);
		spriteHandler->SetTransform(&m_Maxtrix);
	}

	RECT rr = MyHelper::BoxColliderToRect(inSourceRect);

	spriteHandler->Draw(
		texture,
		&rr,
		&center,
		&p,
		colorKey
	);
	spriteHandler->SetTransform(&oldMatrix);
}