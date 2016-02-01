#include "InputLayout.h"

using namespace std;

InputLayout::InputLayout(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{
	
}

InputLayout::~InputLayout()
{
	//释放COM对象
	Util::MapSecondRelease(m_MapIL);
}

void InputLayout::CreateIL(std::wstring ilName, VertexShader* pVertexShader, std::wstring vsName)
{
	ID3D11InputLayout* pIInputLayout;
	ID3DBlob* pIVsCompileBuffer = pVertexShader->GetBlob(vsName);

	D3D11_INPUT_ELEMENT_DESC solidColorLayout[]=
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	unsigned int totalLayoutElement = ARRAYSIZE(solidColorLayout);

	HRESULT d3dHResult = m_pID3DDevice->CreateInputLayout(solidColorLayout,totalLayoutElement,
		pIVsCompileBuffer->GetBufferPointer(),pIVsCompileBuffer->GetBufferSize(),&pIInputLayout);

	pVertexShader->DelBlob(vsName);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("创建输入布局失败！");
		assert(false);
	}

	m_MapIL.insert(pair<wstring,ID3D11InputLayout*>(ilName,pIInputLayout));
}

ID3D11InputLayout* const& InputLayout::GetIL(std::wstring ilName) const
{
	return m_MapIL.find(ilName)->second;
}