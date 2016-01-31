#pragma once

#include "DXHead.h"

class Shader{
public:
	Shader(ID3D11Device* pID3DDevice);
	virtual ~Shader();
protected:
	bool CompileD3DShader(const wchar_t* filePath, char* entry, char* shaderModel, ID3DBlob** buffer );	//±àÒë×ÅÉ«Æ÷½Å±¾
	ID3D11Device* m_pID3DDevice;
};