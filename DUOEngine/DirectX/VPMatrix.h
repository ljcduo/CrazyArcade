#pragma once

#include "DXHead.h"

class VPMatrix
{
public:
	VPMatrix(ID3D11Device* pID3DDevice);
	~VPMatrix();
	void CreateVP(std::wstring vpMatrixName,FLOAT width = 800.0f, FLOAT Height = 600.0f);	//创建视图投影矩阵
	XMMATRIX* const& GetVPMatrix(std::wstring vpMatrixName) const;
	XMMATRIX const CreateMVP(std::wstring vpMatrixName, XMFLOAT2 position, 
		XMFLOAT2 scale = XMFLOAT2(1.0f,1.0f), float rotationZ = 0.0f) const;
private:
	ID3D11Device* m_pID3DDevice;
	std::map<std::wstring,XMMATRIX*> m_MapVPMatrix;
};