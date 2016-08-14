#include "RenderTargetView.h"

using namespace std;

RenderTargetView::RenderTargetView(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{

}

RenderTargetView::~RenderTargetView()
{
	Util::MapSecondRelease(m_MapRTV);
}

void RenderTargetView::CreateRTV(std::wstring rtvName,IDXGISwapChain* pSwapChain)
{
	ID3D11RenderTargetView* pIRenderTargetView;
	ID3D11Texture2D* backBufferTexture;

	HRESULT result = pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&backBufferTexture );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "获得交换链后备缓存失败!" );
		assert(false);
	}

	result = m_pID3DDevice->CreateRenderTargetView( backBufferTexture, 0, &pIRenderTargetView );

	if( backBufferTexture )
		backBufferTexture->Release( );

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "创建渲染目标视图失败!" );
		assert(false);
	}
	
	m_MapRTV.insert(pair<wstring,ID3D11RenderTargetView*>(rtvName,pIRenderTargetView));

}

ID3D11RenderTargetView* const& RenderTargetView::GetRTV(std::wstring rtvName) const
{
	return m_MapRTV.find(rtvName)->second;
}