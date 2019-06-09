#pragma once

#include "SceneManager.h"
#include "PlayScene.h"
#include "PlayScene2.h"
#include "Graphic.h"
#include "KeyBoard.h"

class GameManager {

	HWND hWnd;
	HINSTANCE hInstance;
public:
	GameManager(HWND hWnd, HINSTANCE hInstance);
	~GameManager();
	void ProcessInput();
	void Update(double dt);
	void Render();
};