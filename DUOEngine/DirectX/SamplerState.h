#pragma once

#include "DXHead.h"

class SamplerState
{
public:
	SamplerState(ID3D11Device* pID3DDevice);
	~SamplerState();
	void CreateSS(std::wstring ssName);	//创建采样器状态
	ID3D11SamplerState* const& GetSampler(std::wstring filePath) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,ID3D11SamplerState*> m_MapSampler;
};