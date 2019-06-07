#pragma once
#include "d3dx9.h"
#include <string>
#include "Sprites.h"
#include "iostream"
#include "Camera.h"
#include "Textures.h"
#include "GameConfig.h"

using namespace std;

class Scoreboard
{
private:
	LPD3DXFONT font;
	LPD3DXSPRITE fSprite;
	RECT fRec;
	string s1;
	string t;
	string st;
	string l;
	string p;
	HRESULT	hr;
	LPDIRECT3DTEXTURE9 tex1, tex2, texpower, texborder;
public:
	Scoreboard();
	~Scoreboard();
	void DrawTextTop(LPDIRECT3DDEVICE9 gDevice, int score, int time, int stage, int life, int lifeEnemy, int power);
};