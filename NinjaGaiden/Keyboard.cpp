#include "KeyBoard.h"
#include "Debug.h"
KeyBoard *KeyBoard::instance = NULL;

KeyBoard * KeyBoard::GetInstance() {
	if (instance == NULL)
		instance = new KeyBoard();
	return instance;
}

KeyBoard::KeyBoard() {
	directinput = NULL;
	keyboard = NULL;
}

void KeyBoard::InitKeyboard(HWND _hWnd, HINSTANCE _hInstance) {
	hWnd = _hWnd;
	HRESULT
		hr = DirectInput8Create
		(
			_hInstance,
			DIRECTINPUT_VERSION,
			IID_IDirectInput8, (VOID**)&directinput, NULL
		);
	if (hr != DI_OK) return;

	hr = directinput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	if (hr != DI_OK) return;

	keyboard->SetDataFormat(&c_dfDIKeyboard);
	keyboard->SetCooperativeLevel(_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024; // Arbitary buffer size

	hr = keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = keyboard->Acquire();
	if (hr != DI_OK) return;

	//PLUS
	/*hr = directinput->CreateDevice(GUID_SysMouse, &mouse, NULL);
	mouse->SetDataFormat(&c_dfDIMouse);
	mouse->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE | DISCL_FOREGROUND);
	mouse->Acquire();*/
}


void KeyBoard::ProcessKeyboard() {
	// Collect all key states first
	static HRESULT result;
	// Collect all key states first
	result = keyboard->GetDeviceState(sizeof(keyState), keyState); //Xem phim nao dang nhan

	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			keyboard->Acquire();
		}
	}// ----------------------------------------------

	if (GetKeyDown(DIK_ESCAPE))
	{
		PostMessage(hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = 1024;
	HRESULT hr = keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);
	for (int i = 0; i < 256; i++)
		pressKey[i] = false;
	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			pressKey[KeyCode] = true;
	}

	//PLUS
	/*result = mouse->GetDeviceState(sizeof(mouse_State), (LPVOID)&mouse_State);
	if (FAILED(result)) {
		mouse->Acquire();
		mouse->GetDeviceState(sizeof(mouse_State), (LPVOID)&mouse_State);
	}*/

}

bool KeyBoard::GetKeyDown(int KeyCode) {
	return pressKey[KeyCode];
}

bool KeyBoard::GetKey(int KeyCode) {
	return ((keyState[KeyCode] & 0x80) > 0);
}

bool KeyBoard::GetKeyUp(int KeyCode) {
	return false;
}

D3DXVECTOR2 KeyBoard::GetMouseDis() {
	return D3DXVECTOR2(mouse_State.lX, mouse_State.lY);
}
