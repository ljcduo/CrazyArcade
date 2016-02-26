
#include"Base.h"
#include "ViewPort.h"

int (WINAPIV * __vsnprintf)(char *, size_t, const char*, va_list) = _vsnprintf;

Dx11DemoBase::Dx11DemoBase( ) : m_driverType( D3D_DRIVER_TYPE_NULL ), m_featureLevel( D3D_FEATURE_LEVEL_11_0 ),
                                m_pID3DDevice( 0 ), m_pID3DContext( 0 ), m_pSwapChain( 0 ), m_pRenderTargetView( 0 )
{

}


Dx11DemoBase::~Dx11DemoBase( )
{
    Shutdown( );
}


bool Dx11DemoBase::Initialize( HINSTANCE hInstance, HWND hwnd )
{
	m_hInstance = hInstance;
	m_hwnd = hwnd;

	m_pSwapChain = new SwapChain;

	//创建设备和交换链
	m_pSwapChain->CreateDeviceAndSwapChain(L"SC1",hwnd,&m_pID3DDevice,
		&m_featureLevel,&m_pID3DContext,&m_driverType);

	m_pRenderTargetView = new RenderTargetView(m_pID3DDevice);

	//创建渲染目标视图
    m_pRenderTargetView->CreateRTV(L"RTV1",m_pSwapChain->GetSRV(L"SC1"));
	m_pID3DContext->OMSetRenderTargets( 1, &m_pRenderTargetView->GetRTV(L"RTV1"), 0 );

	//设置视口
    ViewPort viewPort;
	viewPort.CreateVP(L"VP1",800,600);

    m_pID3DContext->RSSetViewports( 1, viewPort.GetVP(L"VP1") );

    return LoadContent( );
}


bool Dx11DemoBase::LoadContent( )
{
    // Override with demo specifics, if any...
    return true;
}


void Dx11DemoBase::UnloadContent( )
{
    // Override with demo specifics, if any...
}


void Dx11DemoBase::Shutdown( )
{
    UnloadContent( );

	SAFE_DELETE(m_pRenderTargetView);
	SAFE_DELETE(m_pSwapChain);
	SAFE_RELEASE(m_pID3DContext);
	SAFE_RELEASE(m_pID3DDevice);
}

