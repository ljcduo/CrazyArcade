#pragma once
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "DXHead.h"

#define KEYDOWN(name, key) ( name[key] & 0x80 )
#define BUTTONDOWN(device, key) ( device.rgbButtons[key] & 0x80 )

class DXInput
{
	enum E_Mouse {E_M_LeftMouse, E_M_RightMouse};

public:
	DXInput(HINSTANCE hInstance, HWND hWnd);
	~DXInput();
	void BeginInputMsg();
	void EndInputMsg();

	bool GetCurrentKeyState(unsigned char keyCode);
	bool GetPrevKeyState(unsigned char keyCode);

	bool GetCurrentMouseState(E_Mouse mouseCode);
	bool GetPrevMouseState(E_Mouse mouseCode);

private:
	LPDIRECTINPUT8 m_directInput;

	LPDIRECTINPUTDEVICE8 m_keyboardDevice;
	char m_keyboardKeys[256];
	char m_prevKeyboardKeys[256];

	LPDIRECTINPUTDEVICE8 m_mouseDevice;
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_prevMouseState;
	long m_mousePosX;
	long m_mousePosY;
	long m_mouseWheel;
};