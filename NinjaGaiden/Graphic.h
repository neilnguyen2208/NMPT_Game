#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "BoxCollider.h"
#include <string>
#include "iostream"
#include "Sprites.h"

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224

using namespace std;

class Graphic {
protected:
	static Graphic *instance;
	HWND hWnd;

	LPDIRECT3D9 d3d = NULL;
	LPDIRECT3DDEVICE9 d3ddv = NULL;

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE spriteHandler = NULL;

	int bufferWidth;
	int bufferHeight;

public:
	//Ham khoi tao
	void Init(HWND hWnd);
	/*void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, BoxCollider r, int alpha);*/
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture);
	LPDIRECT3DDEVICE9 Getdirect3DDevice() {
		return d3ddv;
	}
	LPDIRECT3DSURFACE9 GetBackBuffer() {
		return backBuffer;
	}
	LPD3DXSPRITE GetSpriteHandler() {
		return spriteHandler;
	}
	int GetBackBufferWidth() { return SCREEN_WIDTH; }
	int GetBackBufferHeight() {return SCREEN_HEIGHT; }
	HWND getHWND() { return hWnd; }
	static Graphic *GetInstance();
	~Graphic();
};