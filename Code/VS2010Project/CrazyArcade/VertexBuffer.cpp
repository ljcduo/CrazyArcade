#include "VertexBuffer.h"

using namespace std;


VertexBuffer::VertexBuffer(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{
	
}

VertexBuffer::~VertexBuffer()
{
	Util::MapSecondRelease(m_MapVB);
}

void VertexBuffer::CreateVB(std::wstring vbName, UINT VertexBufferSize)
{
	ID3D11Buffer* pIVertexBuffer;

	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc,sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexDesc.ByteWidth = VertexBufferSize;

	HRESULT d3dHResult = m_pID3DDevice->CreateBuffer(&vertexDesc,NULL,&pIVertexBuffer);

	if(FAILED(d3dHResult))
	{
		DXTRACE_MSG("¥¥Ω®∂•µ„ª∫¥Ê ß∞‹£°");
		assert(false);
	}

	m_MapVB.insert(pair<wstring,ID3D11Buffer*>(vbName,pIVertexBuffer));
}

ID3D11Buffer* const& VertexBuffer::GetVB(std::wstring vbName) const
{
	return m_MapVB.find(vbName)->second;
}