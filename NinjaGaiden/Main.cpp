#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <time.h>
#include "GameManager.h"
#include "GameTime.h"
#include <d3dx9.h>
#define FPS 60
#define SPF 1.0f/FPS
#define WINDOW_CLASS_NAME "BasicdirectX"
#define MAIN_WINDOW_TITLE "01 - FirstProject"
#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}
HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	//them so byte cap phat (khong quan trong)
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	//Ten lop dang ky (QUAN TRONG)
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;
	//Dang ky wc voi he thong
	RegisterClassEx(&wc);
	//Tao cua so
	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_Active | WS_POPUP,
			//x position
			CW_USEDEFAULT,
			//y position
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			//parents window
			NULL,
			NULL,
			hInstance,
			NULL);
	if (!hWnd)
	{
		OutputDebugString("[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return hWnd;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);
	GameManager gameManager(hWnd, hInstance);

	MSG msg;
	bool done = false;
	float dt = 0;

	//--use gettickcount
	//DWORD tick_per_frame = 1000.0f / FPS;
	//float _DeltaTime = 0;
	//DWORD tick_start = GetTickCount();

	DWORD startTime = GetTickCount();
	int slFrame = 0;

	while (!done) {

			GameTime::GetInstance()->StartCounter();
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) done = 1;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			//DWORD now = GetTickCount();
			//DWORD dt = now - tick_start;
			//if (dt >= tick_per_frame) {

			//	if (GetTickCount() - startTime >= 1000) {
			//		DebugOut(L"so luong frame: %d\n", slFrame);
			//		startTime = GetTickCount();
			//		slFrame = 0;
			//	}
			//	else
			//		slFrame++;
			//		
			//	tick_start = GetTickCount();
			//	gameManager.ProcessInput();
			//	gameManager.Update(dt / 1000.0f);
			//	gameManager.Render();
			//}
			//else 
			//	Sleep(tick_per_frame - dt);

			dt += GameTime::GetInstance()->GetCounter();
			if (dt >= SPF) {
				
				if (GetTickCount() - startTime >= 1000) {
					//DebugOut(L"so luong frame/s: %d\n", slFrame);
					startTime = GetTickCount();
					slFrame = 0;
				}
				else
					slFrame++;
				gameManager.ProcessInput();
				gameManager.Update(dt);
				gameManager.Render();
				dt = 0;
			}
			else {
				Sleep(SPF - dt);
				dt = SPF;
			}
	}
	return 0;
}