#pragma once

#include "DXHead.h"

class ShaderResourceView
{
public:
	ShaderResourceView(ID3D11Device* pID3DDevice);
	~ShaderResourceView();
	bool CreateSRV(std::wstring filePath);	//创建着色器资源视图
	//ID3D11ShaderResourceView* const& GetSRV(std::wstring filePath) const;
	ID3D11ShaderResourceView* const& GetSRV(std::wstring filePath, ID3D11ShaderResourceView** result = NULL) const;
	XMFLOAT2 const CalPicSize(std::wstring filePath) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11ShaderResourceView*> m_MapSRV;
};