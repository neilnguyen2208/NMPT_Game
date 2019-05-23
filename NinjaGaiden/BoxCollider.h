#pragma once
#include <d3dx9.h>

class BoxCollider {
public:
	float top;
	float left;
	float bottom;
	float right;
	BoxCollider() : top(0), left(0), right(0), bottom(0) {};
	BoxCollider(float t, float l, float b, float r) : top(t), left(l), bottom(b), right(r) {}
	//Use center position
	BoxCollider(D3DXVECTOR3 position, float width, float height) {
		top = position.y + height / 2;
		bottom = top - height;
		left = position.x - width / 2;
		right = left + width;
	}
	D3DXVECTOR2 GetCenter() { return D3DXVECTOR2((left + right) / 2.0f, (top + bottom) / 2.0f); }
	float GetWidth() { return right - left; }
	float GetHeight() { return top - bottom; }
	void Multiply(float x) {
		top *= x;
		left *= x;
		bottom *= x;
		right *= x;
	};
	void Plus(D3DXVECTOR2 vel) {
		top += vel.y;
		left += vel.x;
		bottom += vel.y;
		right += vel.x;
	}
};