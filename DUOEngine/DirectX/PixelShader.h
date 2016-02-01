#pragma once

#include "Shader.h"


class PixelShader : public Shader
{
public:
	PixelShader(ID3D11Device* pID3DDevice);
	~PixelShader();
	void CreatePS(std::wstring psName, std::wstring filePath);		//创建像素着色器
	ID3D11PixelShader* const& GetPS(std::wstring psName) const;	//获得映射得到的像素着色器
private:
	std::map<std::wstring,ID3D11PixelShader*> m_MapPS;	//文件路径和像素着色器绑定
};