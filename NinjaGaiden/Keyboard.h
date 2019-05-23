#pragma once
#include <queue>
#include <dinput.h>
#include <d3dx9.h>


class KeyBoard {
private:
	static KeyBoard *instance;
	//Doi tuong directinput de nhap input
	LPDIRECTINPUT8 directinput;
	LPDIRECTINPUTDEVICE8 keyboard;

	BYTE keyState[256];							// Trang thai phim
	bool pressKey[256];
	DIDEVICEOBJECTDATA _KeyEvents[1024];		//Du lieu su kien phim

	HWND hWnd;

	//PLUS
	DIMOUSESTATE mouse_State;
	struct DIMOUSESTATE {
		LONG lx;
		LONG ly;
		LONG lz;
		BYTE rgbButton[4];
	};
	LPDIRECTINPUTDEVICE8 mouse;

public:
	static KeyBoard *GetInstance();
	KeyBoard();
	void InitKeyboard(HWND _hWnd, HINSTANCE _hInstance);
	void ProcessKeyboard();
	bool GetKeyDown(int KeyCode);
	bool GetKey(int KeyCode);
	bool GetKeyUp(int KeyCode);
	D3DXVECTOR2 GetMouseDis();
};