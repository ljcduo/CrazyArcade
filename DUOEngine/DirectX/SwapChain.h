#pragma once

#include "DXHead.h"

class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	void CreateDeviceAndSwapChain(std::wstring scName, HWND hwnd,ID3D11Device** pID3DDevice,
		D3D_FEATURE_LEVEL* featureLevel,ID3D11DeviceContext** pID3DContext,
		D3D_DRIVER_TYPE *pDriverType);		//创建设备和交换链
	IDXGISwapChain* const& GetSRV(std::wstring) const;
	void Present(std::wstring scName);
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,IDXGISwapChain*> m_MapSC;
};