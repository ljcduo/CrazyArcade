#include "VPMatrix.h"

using namespace std;

VPMatrix::VPMatrix(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{

}

VPMatrix::~VPMatrix()
{
	Util::MapSecondDelete(m_MapVPMatrix);
}

void VPMatrix::CreateVP(std::wstring vpMatrixName,FLOAT width, FLOAT Height)
{
	XMMATRIX view = XMMatrixIdentity( );
	XMMATRIX projection = XMMatrixOrthographicOffCenterLH( 0.0f, width, 0.0f, Height, 0.1f, 100.0f );

	XMMATRIX TempMultiply = XMMatrixMultiply( view, projection );

	XMMATRIX *vpMatrix = new XMMATRIX(TempMultiply);


	m_MapVPMatrix.insert(pair<wstring,XMMATRIX*>(vpMatrixName,vpMatrix));
}

XMMATRIX* const& VPMatrix::GetVPMatrix(std::wstring vpMatrixName) const
{
	return m_MapVPMatrix.find(vpMatrixName)->second;
}

XMMATRIX const VPMatrix::CreateMVP(std::wstring vpMatrixName, XMFLOAT2 position,
	XMFLOAT2 scale /*= XMFLOAT2(1.0f,1.0f)*/, float rotationZ /*= 0.0f*/) const
{
	XMMATRIX vpMatrix = *GetVPMatrix(vpMatrixName);

	XMMATRIX MATTranslation = XMMatrixTranslation( position.x, position.y, 0.0f );
	XMMATRIX MATRotationZ = XMMatrixRotationZ( rotationZ );
	XMMATRIX MATScale = XMMatrixScaling( scale.x, scale.y, 1.0f );
	XMMATRIX world = MATTranslation * MATScale * MATRotationZ;

	XMMATRIX mvp = XMMatrixMultiply(world,vpMatrix);
	return XMMatrixTranspose( mvp );//ÐèÒª¾ØÕó×ªÖÃ
}