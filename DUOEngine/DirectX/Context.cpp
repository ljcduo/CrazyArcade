#include "Context.h"

Context::Context(ID3D11DeviceContext* pID3DContext) : m_pID3DContext(pID3DContext)
{

}

Context::~Context()
{

}

void Context::ClearRenderTargetView(ID3D11RenderTargetView* pIRenderTargetView)
{
	if(m_pID3DContext == 0)
		assert(false);
	float clearColor[4] = {0.0f,0.0f,0.0f,1.0f};
	m_pID3DContext->ClearRenderTargetView(pIRenderTargetView,clearColor);
}

void Context::IASetInputLayout(ID3D11InputLayout* pIInputLayout)
{
	m_pID3DContext->IASetInputLayout(pIInputLayout);
}

void Context::IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY primitiveTopology)
{
	m_pID3DContext->IASetPrimitiveTopology(primitiveTopology);
}

void Context::VSSetShader(ID3D11VertexShader* pIVertexShader)
{
	m_pID3DContext->VSSetShader(pIVertexShader,0,0);
}

void Context::PSSetShader(ID3D11PixelShader* pIPixelShader)
{
	m_pID3DContext->PSSetShader(pIPixelShader,0,0);
}

void Context::PSSetSamplers(ID3D11SamplerState* pISamplerState)
{
	m_pID3DContext->PSSetSamplers(0,1,&pISamplerState);
}

void Context::PSSetShaderResources(ID3D11ShaderResourceView* pIShaderResourceView)
{
	m_pID3DContext->PSSetShaderResources(0,1,&pIShaderResourceView);
}

void Context::UpdateSubresource(ID3D11Buffer* pIBuffer,XMMATRIX* mvp)
{
	m_pID3DContext->UpdateSubresource(pIBuffer,0,0,mvp,0,0);
}

void Context::VSSetConstantBuffers(ID3D11Buffer* pIBuffer)
{
	m_pID3DContext->VSSetConstantBuffers(0,1,&pIBuffer);
}

void Context::Draw()
{
	m_pID3DContext->Draw(6,0);
}

void Context::OMSetBlendState(ID3D11BlendState* pIBlendState)
{
	m_pID3DContext->OMSetBlendState(pIBlendState,NULL,0xFFFFFFFF);
}




