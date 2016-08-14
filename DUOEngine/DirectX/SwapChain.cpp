#include "SwapChain.h"
#include <DXGI.h>

using namespace std;

SwapChain::SwapChain()
{

}

SwapChain::~SwapChain()
{
	Util::MapSecondRelease(m_MapSC);
}

void SwapChain::CreateDeviceAndSwapChain(std::wstring scName, HWND hwnd,ID3D11Device** pID3DDevice,
	D3D_FEATURE_LEVEL* featureLevel,ID3D11DeviceContext** pID3DContext,D3D_DRIVER_TYPE *pDriverType)
{
	IDXGISwapChain* pISwapChain;

	RECT dimensions;
	GetClientRect( hwnd, &dimensions );

	unsigned int width = dimensions.right - dimensions.left;
	unsigned int height = dimensions.bottom - dimensions.top;

	D3D_DRIVER_TYPE driverTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE
	};

	unsigned int totalDriverTypes = ARRAYSIZE( driverTypes );

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0
	};

	unsigned int totalFeatureLevels = ARRAYSIZE( featureLevels );

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory( &swapChainDesc, sizeof( swapChainDesc ) );
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = width;
	swapChainDesc.BufferDesc.Height = height;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	swapChainDesc.Windowed = true;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	unsigned int creationFlags = 0;

#ifdef _DEBUG
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT result;
	unsigned int driver = 0;

	for( driver = 0; driver < totalDriverTypes; ++driver )
	{
		result = D3D11CreateDeviceAndSwapChain( 0, driverTypes[driver], 0, creationFlags,
			featureLevels, totalFeatureLevels,
			D3D11_SDK_VERSION, &swapChainDesc, &pISwapChain,
			pID3DDevice, featureLevel, pID3DContext );



		//DXGI_SWAP_CHAIN_DESC desc;
		//pISwapChain->GetDesc(&desc);

		if( SUCCEEDED( result ) )
		{
			*pDriverType = driverTypes[driver];
			break;
		}
	}

	if( FAILED( result ) )
	{
		DXTRACE_MSG( "创建D3D设备失败！" );
		assert(false);
	}

	m_MapSC.insert(pair<wstring,IDXGISwapChain*>(scName,pISwapChain));
}

IDXGISwapChain* const& SwapChain::GetSRV(wstring scName) const
{
	return m_MapSC.find(scName)->second;
}

void SwapChain::Present(std::wstring scName)
{
	const_cast<IDXGISwapChain*>(GetSRV(scName))->Present(1,0);
}
