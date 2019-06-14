#include "Camera.h"

Camera *Camera::instance = NULL;

Camera * Camera::GetInstance() {
	if (instance == NULL)
		instance = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);
	return instance;
}

Camera::Camera(int width, int height) {
	this->width = width;
	this->height = height;
	instance = this;
}

void Camera::SetPosition(D3DXVECTOR3 pos) {
	position = pos;
}

void Camera::FollowPlayer(float x, float y) {
	position.x = (int)x;
}

D3DXVECTOR3 Camera::GetPosition() {
	return position;
}

float Camera::GetWidth() {
	return width;
}

float Camera::GetHeight() {
	return height;
}

BoxCollider Camera::GetRect() {
	BoxCollider r;
	r.top = position.y + height / 2;
	r.left = position.x - width / 2;
	r.bottom = r.top - height;
	r.right = r.left + width;
	return r;
}

bool Camera::IsHalfContaint(BoxCollider r) {
	BoxCollider bound = GetRect();
	return ((bound.left < r.right && bound.left > r.left) || (bound.right < r.right && bound.right > r.left) || (bound.bottom > r.bottom && bound.bottom < r.top) || (bound.top > r.bottom && bound.top < r.top));
}

bool Camera::IsCollide(BoxCollider r) {
	BoxCollider bound = GetRect();
	if (r.right < bound.left || r.left > bound.right)
		return false;
	if (r.top < bound.bottom || r.bottom > bound.top)
		return false;
	return true;
}

bool Camera::IsContaint(BoxCollider r) {
	BoxCollider bound = GetRect();
	return (bound.top >= r.top && bound.bottom <= r.bottom && bound.left <= r.left && bound.right >= r.right);
}

Camera::~Camera() {
}
