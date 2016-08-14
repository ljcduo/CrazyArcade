#include "Shader.h"


Shader::Shader(ID3D11Device* pID3DDevice) : m_pID3DDevice(pID3DDevice)
{

}

Shader::~Shader()
{
	
}

bool Shader::CompileD3DShader( const wchar_t* filePath, char* entry, char* shaderModel, ID3DBlob** buffer )
{
	DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* errorBuffer = 0;
	HRESULT result;

	result = D3DX11CompileFromFileW( filePath, 0, 0, entry, shaderModel,
		shaderFlags, 0, 0, buffer, &errorBuffer, 0 );

	if( FAILED( result ) )
	{
		if( errorBuffer != 0 )
		{
			OutputDebugStringA( ( char* )errorBuffer->GetBufferPointer( ) );
			errorBuffer->Release( );
		}

		return false;
	}

	if( errorBuffer != 0 )
		errorBuffer->Release( );

	return true;
}