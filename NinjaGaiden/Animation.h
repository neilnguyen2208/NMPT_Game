#pragma once

#include <unordered_map>
#include "Sprites.h"
#include <vector>
#include "MyHelper.h"
#include "BoxCollider.h"

using namespace std;

class AnimationFrame : public Sprite {
	DWORD time;
public:
	AnimationFrame(LPDIRECT3DTEXTURE9 texture, BoxCollider r, int time = 0.1) : Sprite(r, texture) {
		this->time = time;
	}
	DWORD GetTime() {
		return time;
	}

};
typedef AnimationFrame *LPANIMATION_FRAME;

class Animation {
	DWORD lastFrameTime;
	float defaultTime;
	int currentFrame;
	int totalFrame;
	float currentTotalTime;
	std::vector<LPANIMATION_FRAME> frames;
	float time;

public:
	Animation(float defaultTime = 0.1);
	void AddFrame(LPANIMATION_FRAME frame);
	void AddFrames(LPDIRECT3DTEXTURE9 texture, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = D3DCOLOR_XRGB(255,255,255));
	void AddFramesA(LPDIRECT3DTEXTURE9 texture, int stRows, int fnRows, int columns, int rowNumber, int columnNumber, float timePerFrame = 0.1f, D3DCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	int GetWidthCurrentFrame();
	int GetHeightCurrentFrame();
	void SetCurrentFrame(int frame);
	void Render(D3DXVECTOR3 position = D3DXVECTOR3(), BoxCollider sourceRect= BoxCollider(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255), bool isReverse = false);
	void Update(double dt);
	void ResetAnimation();
	int GetCurrentFrameID();
	bool IsLastFrame(double dt);
	float GetPercentTime();
};
typedef Animation *LPANIMATION;
