#pragma once

#include "Shader.h"
#include <map>

class VertexShader : public Shader
{
public:
	VertexShader(ID3D11Device* pID3DDevice);
	~VertexShader();
	void CreateVS(std::wstring vsName, std::wstring filePath);	//创建顶点着色器
	ID3D11VertexShader* const& GetVS(std::wstring vsName) const;	//获得映射得到的顶点着色器
	ID3DBlob* const& GetBlob(std::wstring vsName) const;			//获得映射得到的顶点着色器编译缓存
	void DelBlob(std::wstring vsName);			//获得映射得到的顶点着色器编译缓存
private:
	std::map<std::wstring,ID3D11VertexShader*> m_MapVS;	//文件路径和顶点着色器绑定
	std::map<std::wstring,ID3DBlob*> m_MapBlob;			//文件路径和编译的顶点着色器缓存绑定
};