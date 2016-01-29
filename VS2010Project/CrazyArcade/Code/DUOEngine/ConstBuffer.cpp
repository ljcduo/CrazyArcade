#include "ConstBuffer.h"

using namespace std;

ConstBuffer::ConstBuffer(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{
	
}

ConstBuffer::~ConstBuffer()
{
	Util::MapSecondRelease(m_MapCB);
}

void ConstBuffer::CreateCB(wstring cbName)
{
	ID3D11Buffer* pImvpCB;

	D3D11_BUFFER_DESC constDesc;
	ZeroMemory(&constDesc,sizeof(constDesc));
	constDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constDesc.ByteWidth = sizeof(XMMATRIX);
	constDesc.Usage = D3D11_USAGE_DEFAULT;

	HRESULT d3dHResult = m_pID3DDevice->CreateBuffer(&constDesc,0,&pImvpCB);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("创建常量缓存失败！");
		assert(false);
	}

	m_MapCB.insert(pair<wstring,ID3D11Buffer*>(cbName,pImvpCB));
}

ID3D11Buffer* const& ConstBuffer::GetCB(std::wstring cbName) const
{
	return m_MapCB.find(cbName)->second;
}