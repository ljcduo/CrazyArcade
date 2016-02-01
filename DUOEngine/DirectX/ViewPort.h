#pragma once

#include "DXHead.h"

class ViewPort
{
public:
	ViewPort();
	~ViewPort();
	void CreateVP(std::wstring vpName,int width,int height);			//创建视口
	D3D11_VIEWPORT* const& GetVP(std::wstring vpName) const;	//获得映射得到的视口
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,D3D11_VIEWPORT*> m_MapVP;	
};