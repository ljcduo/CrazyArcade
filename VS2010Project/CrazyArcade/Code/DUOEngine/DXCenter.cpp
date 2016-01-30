#include "DXCenter.h"
#include "LGCenter.h"
#include "DXInput.h"
#include "Object.h"
#include "Rect.h"

#include <assert.h>

using namespace std;

const wstring SHADERPATH = L"Shader\\TextureMap.fx";
SINGLETON_INHERIT_BASE_CPP(DXCenter);

DXCenter::DXCenter() : m_pInputLayout(0),m_pPixelShader(0),m_pVertexShader(0),
	m_pShaderResourceView(0),m_pSamplerState(0),m_pVertexBuffer(0),m_pConstBuffer(0),
	m_pVPMatrix(0), m_pBlendState(0), m_pContext(0), m_pDXInput(0)
{

}

DXCenter::~DXCenter()
{
	UnloadContent();
}

bool DXCenter::LoadContent()
{
	//载入DX资源
	m_pPixelShader = new PixelShader(m_pID3DDevice);
	m_pVertexShader = new VertexShader(m_pID3DDevice);
	m_pInputLayout = new InputLayout(m_pID3DDevice);
	m_pShaderResourceView = new ShaderResourceView(m_pID3DDevice);
	m_pSamplerState = new SamplerState(m_pID3DDevice);
	m_pVertexBuffer = new VertexBuffer(m_pID3DDevice);
	m_pConstBuffer = new ConstBuffer(m_pID3DDevice);
	m_pVPMatrix = new VPMatrix(m_pID3DDevice);
	m_pBlendState = new BlendState(m_pID3DDevice);
	m_pContext = new Context(m_pID3DContext);
	m_pDXInput = new DXInput(m_hInstance,m_hwnd);

	m_pPixelShader->CreatePS(L"PS1",SHADERPATH);
	m_pVertexShader->CreateVS(L"VS1",SHADERPATH);
	m_pInputLayout->CreateIL(L"IL1",m_pVertexShader,L"VS1");
	m_pSamplerState->CreateSS(L"SS1");
	m_pVertexBuffer->CreateVB(L"VB1",sizeof(VertexPos)*6);
	m_pConstBuffer->CreateCB(L"CB1");
	m_pVPMatrix->CreateVP(L"VP1");
	m_pBlendState->CreateBS(L"BS1");


	m_pContext->OMSetBlendState(m_pBlendState->GetBlendState(L"BS1"));



	return true;
}

void DXCenter::UnloadContent()
{
	//卸载DX资源
	SAFE_DELETE(m_pDXInput);
	SAFE_DELETE(m_pBlendState);
	SAFE_DELETE(m_pVPMatrix);
	SAFE_DELETE(m_pConstBuffer);
	SAFE_DELETE(m_pVertexBuffer);
	SAFE_DELETE(m_pSamplerState);
	SAFE_DELETE(m_pShaderResourceView);
	SAFE_DELETE(m_pInputLayout);
	SAFE_DELETE(m_pVertexShader);
	SAFE_DELETE(m_pPixelShader);
	SAFE_DELETE(m_pContext);
}

void DXCenter::DXUpdate( float dt )
{
	//更新游戏逻辑

	InputControl();

	LGCenter::Instance()->Update();

	//载入场景
	//为当前场景的游戏对象创建着色器资源视图
	vector<Object*> UnLoadObjVec = LGCenter::Instance()->GetCurrentScene()->GetUnLoadObject();

	for (vector<Object*>::const_iterator itr = UnLoadObjVec.begin(); itr != UnLoadObjVec.end(); itr++)
	{
		m_pShaderResourceView->CreateSRV((*itr)->GetCurrentSprite().GetPicPath());
		XMFLOAT2 picSize = m_pShaderResourceView->CalPicSize((*itr)->GetCurrentSprite().GetPicPath());//计算图片大小
		(*itr)->HavaCurrentSprite().SetPicSize(Point(picSize.x,picSize.y));
		(*itr)->UpdateSpriteRect();
		if ((*itr)->GetVisiable())
		{
			(*itr)->SetDirtySource();
		}
	}

	LGCenter::Instance()->GetCurrentScene()->DirtyRectInfect();
	LGCenter::Instance()->GetCurrentScene()->hadLoadAll();
	
	
}

void DXCenter::DXRender()
{
	m_pContext->IASetInputLayout(m_pInputLayout->GetIL(L"IL1"));
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->VSSetShader(m_pVertexShader->GetVS(L"VS1"));
	m_pContext->PSSetShader(m_pPixelShader->GetPS(L"PS1"));
	m_pContext->PSSetSamplers(m_pSamplerState->GetSampler(L"SS1"));

	Render();

	Scene* currentScene = LGCenter::Instance()->GetCurrentScene();
	CHECK_TO_RETURN(currentScene);

	//将当前场景的游戏对象绘制
	vector<Object*> currentObjVec = currentScene->GetAllDirtyObject();
	for (vector<Object*>::const_iterator itrObj = currentObjVec.begin(); itrObj != currentObjVec.end(); ++itrObj)
	{
		if (!(*itrObj)->GetVisiable()) //不可见物体不需要重绘
		{
			continue;
		}

		std::vector<LGRect> RectVec = (*itrObj)->GetRectDirty();

		for (std::vector<LGRect>::const_iterator itrRect = RectVec.begin(); 
			itrRect != RectVec.end(); ++itrRect)
		{
			Sprite const& currentSprite = (*itrObj)->GetCurrentSprite();

			wstring currentPath = currentSprite.GetPicPath();

			m_pContext->PSSetShaderResources(m_pShaderResourceView->GetSRV(currentPath));

			m_pContext->FreshPic<VertexPos>(m_pVertexBuffer->GetVB(L"VB1"), 
				currentSprite.GetPicSizeWidth(), currentSprite.GetPicSizeHeight(),
				currentSprite.GetCurrentRow(), currentSprite.GetCurrentCol(), 
				(*itrObj)->GetSpriteRect(),(*itrRect));


			m_pContext->IASetVertexBuffers<VertexPos>(m_pVertexBuffer->GetVB(L"VB1"));


			XMMATRIX mvp = m_pVPMatrix->CreateMVP(L"VP1",
				XMFLOAT2((*itrRect).GetX(),(*itrRect).GetY()));

			m_pContext->UpdateSubresource(m_pConstBuffer->GetCB(L"CB1") ,&mvp);
			m_pContext->VSSetConstantBuffers(m_pConstBuffer->GetCB(L"CB1"));

			m_pContext->Draw();
		}

		(*itrObj)->SetDirty(false);


	}



	LGCenter::Instance()->GetCurrentScene()->ClearDirtyObject();
	

	m_pSwapChain->Present(L"SC1");
	
}


void DXCenter::Update()
{

}

void DXCenter::Render()
{
	
}

HINSTANCE const& DXCenter::GetHInstance() const
{
	return m_hInstance;
}

HWND const& DXCenter::GetHWnd() const
{
	return m_hwnd;
}

void DXCenter::InputControl()
{
	m_pDXInput->BeginInputMsg();

	unsigned char DXKeyCode[] = {DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT,DIK_SPACE};
	LGInput::E_KeyName LGKeyCode[] = {LGInput::E_KeyUp, LGInput::E_KeyDown, LGInput::E_KeyLeft, LGInput::E_KeyRight,
										LGInput::E_KeySpace};

	for (int i = 0; i != LGInput::E_KeyNum; i++ )
	{
		SYNCKeyBoard(DXKeyCode[i],LGKeyCode[i]);
	}

	m_pDXInput->EndInputMsg();
}

void DXCenter::SYNCKeyBoard(unsigned char DXKeyCode, LGInput::E_KeyName LGKeyCode)
{
	if (m_pDXInput->GetCurrentKeyState(DXKeyCode))
	{
		LGInput::Instance()->SetCurrentKey(LGKeyCode,true);
	}
	else
	{
		LGInput::Instance()->SetCurrentKey(LGKeyCode,false);
	}

	if (m_pDXInput->GetPrevKeyState(DXKeyCode))
	{
		LGInput::Instance()->SetPrevKey(LGKeyCode,true);
	}
	else
	{
		LGInput::Instance()->SetPrevKey(LGKeyCode,false);
	}
}