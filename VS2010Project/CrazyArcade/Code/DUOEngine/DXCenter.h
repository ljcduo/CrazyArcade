//DXCenter负责调配DX资源，绘制场景

#pragma once
#include "Base.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "ShaderResourceView.h"
#include "SamplerState.h"
#include "VertexBuffer.h"
#include "ConstBuffer.h"
#include "VPMatrix.h"
#include "BlendState.h"
#include "Context.h"
#include "DXInput.h"

#include "LGCenter.h"
#include "LGInput.h"

struct VertexPos
{
	XMFLOAT3 pos;
	XMFLOAT2 tex0;
};

class DXCenter : public Dx11DemoBase
{
	SINGLETON_NOCTOR(DXCenter);
public:
	bool LoadContent();
	void UnloadContent();

	void Update( float dt );
	void Render();

	HINSTANCE const& GetHInstance() const;
	HWND const& GetHWnd() const;
	void InputControl();
	void SYNCKeyBoard(unsigned char DXKeyCode, LGInput::E_KeyName LGKeyCode);
private:
	//DX资源
	PixelShader* m_pPixelShader;
	VertexShader* m_pVertexShader;
	InputLayout* m_pInputLayout;
	ShaderResourceView* m_pShaderResourceView;
	SamplerState* m_pSamplerState;
	VertexBuffer* m_pVertexBuffer;
	ConstBuffer* m_pConstBuffer;
	VPMatrix* m_pVPMatrix;
	BlendState* m_pBlendState;
	Context* m_pContext;
	DXInput* m_pDXInput;
};

#define g_pCenter DXCenter::Instance()