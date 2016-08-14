#include "DXInput.h"
#include <assert.h>

DXInput::~DXInput()
{
	if( m_keyboardDevice )
	{ 
		m_keyboardDevice->Unacquire( );
	}

	SAFE_RELEASE(m_keyboardDevice);
	SAFE_RELEASE(m_directInput);
}

DXInput::DXInput(HINSTANCE hInstance, HWND hWnd)
{
	//初始化键盘输入设备
	ZeroMemory( m_keyboardKeys, sizeof( m_keyboardKeys ) );
	ZeroMemory( m_prevKeyboardKeys, sizeof( m_prevKeyboardKeys ) );

	HRESULT result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, ( void** )&m_directInput, 0 );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "创建DirectInput键盘设备对象失败！" );
		assert(false);
	}

	result = m_directInput->CreateDevice( GUID_SysKeyboard, &m_keyboardDevice, 0 );

	if( FAILED( result ) )
	{ 
		DXTRACE_MSG( "创建DirectInput键盘设备失败！" );
		assert(false);
	}

	result = m_keyboardDevice->SetDataFormat( &c_dfDIKeyboard );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "设置DirectInput键盘设备数据格式失败！" );
		assert(false);
	}

	result = m_keyboardDevice->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "设置DirectInput键盘设备合作级别失败！" );
		assert(false);
	}

	result = m_keyboardDevice->Acquire( );

	if( FAILED( result ) )
	{ 
		DXTRACE_MSG( "第一次请求DirectInput键盘设备失败！" );
	}

	//初始化鼠标设备
	m_mousePosX = m_mousePosY = m_mouseWheel = 0;

	result = m_directInput->CreateDevice( GUID_SysMouse, &m_mouseDevice, 0 );

	if( FAILED( result ) )
	{ 
		DXTRACE_MSG( "创建DirectInput鼠标设备失败！" );
		assert(false);
	}

	result = m_mouseDevice->SetDataFormat( &c_dfDIMouse );

	if( FAILED( result ) )
	{ 
		DXTRACE_MSG( "设置DirectInput鼠标设备数据格式失败！" );
		assert(false);
	}

	result = m_mouseDevice->SetCooperativeLevel( hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE );

	if( FAILED( result ) )
	{ 
		DXTRACE_MSG( "设置DirectInput鼠标设备合作级别失败！" );
		assert(false);
	}

	result = m_mouseDevice->Acquire( );

	if( FAILED( result ) )
	{ 
		DXTRACE_MSG( "第一次请求DirectInput鼠标设备失败！" );
	}
}


bool DXInput::GetCurrentKeyState(unsigned char keyCode)
{
	if (KEYDOWN( m_keyboardKeys, keyCode ))
		return true;
	return false;
}

bool DXInput::GetPrevKeyState(unsigned char keyCode)
{
	if (KEYDOWN( m_prevKeyboardKeys, keyCode ))
		return true;
	return false;
}

void DXInput::BeginInputMsg()
{
	//更新键盘设备输入信息
	HRESULT hr = m_keyboardDevice->GetDeviceState( sizeof( m_keyboardKeys ), ( LPVOID )&m_keyboardKeys );

	if( FAILED( hr ) ) //设备丢失后重新取回
	{
		hr = m_keyboardDevice->Acquire( );
		while( hr == DIERR_INPUTLOST )
		{
			hr = m_keyboardDevice->Acquire( );
		}
	}

	//更新鼠标设备输入信息
	hr = m_mouseDevice->GetDeviceState( sizeof ( m_mouseState ), ( LPVOID ) &m_mouseState );

	if( FAILED( hr ) ) //设备丢失后重新取回
	{
		hr = m_mouseDevice->Acquire( );
		while( hr == DIERR_INPUTLOST )
		{
			hr = m_mouseDevice->Acquire( );
		}
	}

	m_mousePosX += m_mouseState.lX;
	m_mousePosY += m_mouseState.lY;
	m_mouseWheel += m_mouseState.lZ;

}

void DXInput::EndInputMsg()
{
	memcpy( m_prevKeyboardKeys, m_keyboardKeys, sizeof( m_keyboardKeys) );
	memcpy( &m_prevMouseState, &m_mouseState, sizeof( m_mouseState ) );
}

bool DXInput::GetCurrentMouseState(E_Mouse mouseCode)
{
	if( BUTTONDOWN( m_mouseState, mouseCode )) 
		return true;
	return false;
}

bool DXInput::GetPrevMouseState(E_Mouse mouseCode)
{
	if( BUTTONDOWN( m_prevMouseState, mouseCode )) 
		return true;
	return false;
}

