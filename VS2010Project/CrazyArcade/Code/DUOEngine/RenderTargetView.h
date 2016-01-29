#pragma once

#include "DXHead.h"

class RenderTargetView
{
public:
	RenderTargetView(ID3D11Device* pID3DDevice);
	~RenderTargetView();
	void CreateRTV(std::wstring rtvName,IDXGISwapChain* pSwapChain);	//创建着色器资源视图
	ID3D11RenderTargetView* const& GetRTV(std::wstring rtvName) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11RenderTargetView*> m_MapRTV;
};