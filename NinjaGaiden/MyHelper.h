#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include "BoxCollider.h"
#include <math.h>


class MyHelper {
public:
	static RECT BoxColliderToRect(BoxCollider col);
	static float Clamp(float x, float a, float z);
	static float Distance(float x, float y);
};