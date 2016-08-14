#include "VertexShader.h"
#include <d3d11.h>

using namespace std;

VertexShader::VertexShader(ID3D11Device* pID3DDevice) : Shader(pID3DDevice)
{

}

VertexShader::~VertexShader()
{
	//释放COM对象
	Util::MapSecondRelease(m_MapVS);
	Util::MapSecondRelease(m_MapBlob);
};

void VertexShader::CreateVS(std::wstring vsName, std::wstring filePath)
{
	ID3D11VertexShader* pIVertexShader;

	ID3DBlob* pIVsCompileBuffer = 0;

	bool compileResult = CompileD3DShader(filePath.c_str(),"VS_Main","vs_4_0",&pIVsCompileBuffer);

	if(compileResult == false)
	{
		DXTRACE_MSG("编译顶点着色器发生错误！");
		assert(false);
	}

	HRESULT d3dHResult;


	d3dHResult = m_pID3DDevice->CreateVertexShader(pIVsCompileBuffer->GetBufferPointer(),
		pIVsCompileBuffer->GetBufferSize(),0,&pIVertexShader);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("创建顶点着色器发生错误！");

		SAFE_RELEASE(pIVsCompileBuffer);

		assert(false);
	}

	m_MapVS.insert(pair<wstring,ID3D11VertexShader*>(vsName,pIVertexShader));
	m_MapBlob.insert(pair<wstring,ID3DBlob*>(vsName,pIVsCompileBuffer));
}

ID3D11VertexShader* const& VertexShader::GetVS(std::wstring vsName) const
{
	return m_MapVS.find(vsName)->second;
}

ID3DBlob* const& VertexShader::GetBlob(std::wstring vsName) const
{
	return m_MapBlob.find(vsName)->second;
}

void VertexShader::DelBlob(std::wstring vsName)
{
	SAFE_RELEASE(m_MapBlob.find(vsName)->second);
	m_MapBlob.erase(m_MapBlob.find(vsName));
}
