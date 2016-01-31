#pragma once

#include "DXHead.h"

class VertexBuffer
{
public:
	VertexBuffer(ID3D11Device* pID3DDevice);
	~VertexBuffer();
	void CreateVB(std::wstring vbName, UINT VertexBufferSize);	//´´½¨¶¥µã»º´æ
	ID3D11Buffer* const& GetVB(std::wstring vbName) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11Buffer*> m_MapVB;
};