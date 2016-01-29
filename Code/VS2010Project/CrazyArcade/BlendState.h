#pragma once

#include "DXHead.h"

class BlendState
{
public:
	BlendState(ID3D11Device* pID3DDevice);
	~BlendState();
	void CreateBS(std::wstring bsName);
	ID3D11BlendState* const& GetBlendState(std::wstring blendName) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11BlendState*> m_MapBlendState;
};