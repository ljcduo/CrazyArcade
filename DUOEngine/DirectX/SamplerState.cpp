#include "SamplerState.h"

using namespace std;

SamplerState::SamplerState(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{

}

SamplerState::~SamplerState()
{
	//释放COM对象
	Util::MapSecondRelease(m_MapSampler);
}

void SamplerState::CreateSS(std::wstring ssName)
{
	ID3D11SamplerState* pISamplerState;

	D3D11_SAMPLER_DESC colorMapDesc;
	ZeroMemory(&colorMapDesc,sizeof(colorMapDesc));
	colorMapDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	colorMapDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	colorMapDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	colorMapDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT d3dHResult = m_pID3DDevice->CreateSamplerState(&colorMapDesc,&pISamplerState);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("创建采样器状态失败！");
		assert(false);
	}
	
	m_MapSampler.insert(pair<wstring,ID3D11SamplerState*>(ssName,pISamplerState));

}

ID3D11SamplerState* const& SamplerState::GetSampler(std::wstring filePath) const
{
	return m_MapSampler.find(filePath)->second;
}