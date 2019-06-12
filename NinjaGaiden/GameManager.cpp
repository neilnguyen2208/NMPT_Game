#include "GameManager.h"

#include"Player.h"
#include"Camera.h"
GameManager::GameManager(HWND hWnd, HINSTANCE hInstance) {
	Graphic::GetInstance()->Init(hWnd);
	KeyBoard::GetInstance()->InitKeyboard(hWnd, hInstance);
	SceneManager::GetInstance()->CreateScene(new PlayScene());
	//SceneManager::GetInstance()->CreateScene(new PlayScene2());
	this->hWnd = hWnd;
	this->hInstance = hInstance;
}

GameManager::~GameManager() {

}

void GameManager::Update(double dt) {
	//neu khong chuyen canh thi update
	if (!SceneManager::GetInstance()->isSceneTransitioning())
		SceneManager::GetInstance()->GetCurrentScene()->Update(dt);
	/*else {				
		SceneTransition::GetInstance()->Update(dt);
		SceneManager::GetInstance()->UpdateWithEffect(dt);
	}*/
	
}

void GameManager::Render() {
	auto device = Graphic::GetInstance()->Getdirect3DDevice();
	auto spriteHandler = Graphic::GetInstance()->GetSpriteHandler();
	auto scene = SceneManager::GetInstance()->GetCurrentScene();
	//device->Clear(0, NULL, D3DCLEAR_TARGET, scene->GetBackColor(), 0.0f, 0);
	//if (!SceneManager::GetInstance()->isSceneTransitioning())
		SceneManager::GetInstance()->GetCurrentScene()->Render();
	
	//RENDER
	{
		device->BeginScene();
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		/*Graphic::DrawTextTop(1, 2, 3, 4, 5);*/
		scene->Render();
		spriteHandler->End();
		device->EndScene();
	}
	device->Present(NULL, NULL, NULL, NULL);
	
}

void GameManager::ProcessInput() {
	KeyBoard::GetInstance()->ProcessKeyboard();
}

