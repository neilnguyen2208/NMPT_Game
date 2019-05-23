#include "Graphic.h"

Graphic *Graphic::instance = NULL;

void Graphic::Init(HWND hWnd) {
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	this->hWnd = hWnd;
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	
	d3dpp.BackBufferHeight = 224;
	d3dpp.BackBufferWidth = 256;
	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv
	);
	if (d3ddv == NULL)
		OutputDebugString(L"[ERROR] CreateDevice failed\n");
	d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);
	D3DXCreateSprite(d3ddv, &spriteHandler);
}

//void Graphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha) {
//	D3DXVECTOR3 position(x, y, 0);
//	BoxCollider r;
//	r.top = top;
//	r.left = left;
//	r.right = right;
//	r.bottom = bottom;
//	spriteHandler->Draw(texture, &r, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
//}
//
//void Graphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, BoxCollider r, int alpha) {
//	D3DXVECTOR3 position(x, y, 0);
//	spriteHandler->Draw(texture, &r, NULL, &position, D3DCOLOR_ARGB(alpha, 255, 255, 255));
//}
//
//void Graphic::Draw(float x, float y, LPDIRECT3DTEXTURE9 texture) {
//	D3DXVECTOR3 position(x, y, 0);
//	spriteHandler->Draw(texture, NULL, NULL, &position, D3DCOLOR_ARGB(255, 255, 255, 255));
//}

Graphic * Graphic::GetInstance() {
	if (instance == NULL)
		instance = new Graphic();
	return instance;
}

Graphic::~Graphic() {
	if (backBuffer != NULL)
		backBuffer->Release();
	if (d3ddv != NULL)
		d3ddv->Release();
	if (d3d != NULL)
		d3d->Release();
}
