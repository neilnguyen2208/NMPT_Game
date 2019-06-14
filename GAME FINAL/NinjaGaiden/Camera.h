#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "MyHelper.h"


#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 224


class Camera {
private:
	D3DXVECTOR3 position;
	float width;
	float height;
	static Camera *instance;
public:
	static Camera *GetInstance();
	Camera(int width, int height);
	void SetPosition(D3DXVECTOR3 pos);
	void FollowPlayer(float x, float y);
	D3DXVECTOR3 GetPosition();
	float GetWidth();
	float GetHeight();
	BoxCollider GetRect();
	bool IsHalfContaint(BoxCollider r);
	bool IsCollide(BoxCollider r);
	bool IsContaint(BoxCollider r);
	~Camera();
};