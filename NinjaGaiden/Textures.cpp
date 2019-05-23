#include "Textures.h"
#include "Debug.h"
#include "GameManager.h"
#include "Textures.h"
Textures * Textures::instance = NULL;

Textures::Textures() {
}

void Textures::Add(int id, LPCSTR path, D3DCOLOR transparentColor) {
	if (textures[id])
		return;
	D3DXIMAGE_INFO infor;
	HRESULT result = D3DXGetImageInfoFromFileA(path, &infor);
	if (result != D3D_OK) {
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", path);
		return;
	}
	LPDIRECT3DDEVICE9 d3ddv = Graphic::GetInstance()->Getdirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;
	result = D3DXCreateTextureFromFileExA(
		d3ddv,
		path,
		infor.Width,							// Texture width
		infor.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,///////////////////
		&infor,
		NULL,
		&texture);

	if (result != D3D_OK) {
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}
	textures[id] = texture;
	//DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, path);
}

bool Textures::HasContained(int id) {
	return textures.count(id);
}

LPDIRECT3DTEXTURE9 Textures::Get(unsigned int i) {
	return textures[i];
}

Textures * Textures::GetInstance() {
	if (instance == NULL)
		instance = new Textures();
	return instance;
}
