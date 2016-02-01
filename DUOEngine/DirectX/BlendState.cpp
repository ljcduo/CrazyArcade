#include "BlendState.h"

using namespace std;

BlendState::BlendState(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{

}

BlendState::~BlendState()
{
	Util::MapSecondRelease(m_MapBlendState);
}

void BlendState::CreateBS(std::wstring bsName)
{
	ID3D11BlendState* pIAlphaBlendState;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc,sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	m_pID3DDevice->CreateBlendState(&blendDesc,&pIAlphaBlendState);

	m_MapBlendState.insert(pair<wstring,ID3D11BlendState*>(bsName,pIAlphaBlendState));
}

ID3D11BlendState* const& BlendState::GetBlendState(std::wstring blendName) const
{
	return m_MapBlendState.find(blendName)->second;
}