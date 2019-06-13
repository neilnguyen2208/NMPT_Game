#include "GameManager.h"
#include "Player.h"
#include "Camera.h"

GameManager::GameManager(HWND hWnd, HINSTANCE hInstance) {
	Graphic::GetInstance()->Init(hWnd);
	KeyBoard::GetInstance()->InitKeyboard(hWnd, hInstance);
	CSoundChoose::GetInstance()->InitCSoundChoose(hWnd);
	SceneManager::GetInstance()->CreateScene(new PlayScene());
	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

GameManager::~GameManager() {

}

void GameManager::Update(double dt) {
	if (!SceneManager::GetInstance()->isSceneTransitioning())
		SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
}

void GameManager::Render() {
	auto device = Graphic::GetInstance()->Getdirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	SceneManager::GetInstance()->GetCurrentScene()->Render();
	
	//RENDER
	{
		device->BeginScene();
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		scene->Render();
		spriteHandler->End();
		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
	
}

void GameManager::ProcessInput() {
	KeyBoard::GetInstance()->ProcessKeyboard();
}

