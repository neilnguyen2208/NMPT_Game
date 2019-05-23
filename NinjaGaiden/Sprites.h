#pragma once
#include <unordered_map>
#include <time.h>
#include <Windows.h>
#include <d3dx9.h>
#include "MyHelper.h"
#include "Graphic.h"
#include "BoxCollider.h"


using namespace std;

class Sprite {
protected:

	BoxCollider rect;
	LPDIRECT3DTEXTURE9 texture;
	int width, height;

	LPD3DXSPRITE spriteHandler;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR2 m_Translation;

public:
	Sprite(BoxCollider r, LPDIRECT3DTEXTURE9 tex);
	int GetWidth();
	int GetHeight();
	void SetWidth(int width);
	void SetHeight(int height);
	bool IsRect(BoxCollider r);
	LPDIRECT3DTEXTURE9 GetTexture() { return texture; }
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), BoxCollider r = BoxCollider(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255), bool reverse = false);
};
typedef Sprite *LPSPRITE;