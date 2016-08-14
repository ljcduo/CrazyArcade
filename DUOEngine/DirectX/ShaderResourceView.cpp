#include "ShaderResourceView.h"

using namespace std;

ShaderResourceView::ShaderResourceView(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{

}

ShaderResourceView::~ShaderResourceView()
{
	//释放COM对象
	Util::MapSecondRelease(m_MapSRV);
}

bool ShaderResourceView::CreateSRV(std::wstring filePath)
{
	ID3D11ShaderResourceView *pISRV = 0;

	GetSRV(filePath,&pISRV);

	if(pISRV != NULL)
	{
		return false;	//防止重复创建SRV
	}


	HRESULT d3dHResult = D3DX11CreateShaderResourceViewFromFileW(m_pID3DDevice,filePath.c_str(),0,0,&pISRV,0);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("加载纹理图片失败！");
		assert(false);
	}

	m_MapSRV.insert(pair<wstring,ID3D11ShaderResourceView*>(filePath,pISRV));
	return true;
}

ID3D11ShaderResourceView* const& ShaderResourceView::GetSRV(std::wstring filePath, ID3D11ShaderResourceView** result) const
{
	std::map<std::wstring,ID3D11ShaderResourceView*>::const_iterator FindResult = m_MapSRV.find(filePath);
	if (FindResult != m_MapSRV.end())
	{
		return FindResult->second;
	}
	*result = NULL;
	return NULL;
}

XMFLOAT2 const ShaderResourceView::CalPicSize(std::wstring filePath) const
{
	ID3D11ShaderResourceView* pISpriteSRV = GetSRV(filePath);
	ID3D11Texture2D* pISpriteTex;
	float TextureWidth = 0.0f,TextureHeight = 0.0f;

	pISpriteSRV->GetResource( (ID3D11Resource**) &pISpriteTex);
	D3D11_TEXTURE2D_DESC SpriteTexDesc;
	pISpriteTex->GetDesc(&SpriteTexDesc);

	TextureWidth = static_cast<float>(SpriteTexDesc.Width);
	TextureHeight = static_cast<float>(SpriteTexDesc.Height);

	SAFE_RELEASE(pISpriteTex);

	return XMFLOAT2(TextureWidth,TextureHeight);
}
