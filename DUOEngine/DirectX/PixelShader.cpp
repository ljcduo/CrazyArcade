#include "PixelShader.h"

using namespace std;

PixelShader::PixelShader(ID3D11Device* pID3DDevice) : Shader(pID3DDevice)
{

}

PixelShader::~PixelShader()
{
	//释放COM对象
	Util::MapSecondRelease(m_MapPS);
}
void PixelShader::CreatePS(std::wstring psName, std::wstring filePath)
{
	ID3DBlob* pIPsCompileBuffer = 0;
	ID3D11PixelShader* pIPixelShader = 0;

	bool compileResult = CompileD3DShader(filePath.c_str(),"PS_Main","ps_4_0",&pIPsCompileBuffer);
	if(compileResult == false)
	{
		DXTRACE_MSG("编译像素着色器失败");
		assert(false);
	}

	HRESULT d3dHResult = m_pID3DDevice->CreatePixelShader(pIPsCompileBuffer->GetBufferPointer(),pIPsCompileBuffer->GetBufferSize(),0,&pIPixelShader);

	SAFE_RELEASE(pIPsCompileBuffer);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("创建像素着色器失败！");
		assert(false);
	}

	m_MapPS.insert(pair<wstring,ID3D11PixelShader*>(psName,pIPixelShader));
}

ID3D11PixelShader* const& PixelShader::GetPS(std::wstring psName) const
{
	return m_MapPS.find(psName)->second;
}