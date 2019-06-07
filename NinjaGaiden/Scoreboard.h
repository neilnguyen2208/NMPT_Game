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
	string f;
	string p;
	HRESULT	hr;
	LPDIRECT3DTEXTURE9 texblood1, texblood2, texpower, texborder, texskill1, texskill2, texskill3;
public:
	Scoreboard();
	~Scoreboard();
	void DrawTextTop(LPDIRECT3DDEVICE9 gDevice, int score, int fate, int time, int stage, int blood, int bloodEnemy, int power, int skill);
};