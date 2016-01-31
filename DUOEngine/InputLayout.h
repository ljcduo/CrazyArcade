#pragma once

#include "DXHead.h"
#include <map>
#include "VertexShader.h"

class InputLayout
{
public:
	InputLayout(ID3D11Device* pID3DDevice);
	~InputLayout();
	void CreateIL(std::wstring ilName, VertexShader* pVertexShader, std::wstring vsName);
	ID3D11InputLayout* const& GetIL(std::wstring ilName) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11InputLayout*> m_MapIL;
};