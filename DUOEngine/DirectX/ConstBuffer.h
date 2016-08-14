#pragma once

#include "DXHead.h"

class ConstBuffer
{
public:
	ConstBuffer(ID3D11Device* pID3DDevice);
	~ConstBuffer();
	void CreateCB(std::wstring cbName);	//创建常量缓存
	ID3D11Buffer* const& GetCB(std::wstring cbName) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11Buffer*> m_MapCB;
};