#include "DXCenter.h"
#include "LGCenter.h"
#include "DXInput.h"
#include "Object.h"
#include "Rect.h"

#include <assert.h>

using namespace std;

const wstring SHADERPATH = L"Shader\\TextureMap.fx";


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
	//更新输入信息
	InputUpdate();

	//更新游戏逻辑
	g_pLGCenter->Update();

	//载入场景中未初始化的对象

	vector<Object*> UnLoadObjVec = g_pLGCenter->GetCurrentScene()->GetUnLoadObject();

	for (vector<Object*>::const_iterator itr = UnLoadObjVec.begin(); itr != UnLoadObjVec.end(); itr++)
	{
		//为当前场景的游戏对象创建着色器资源视图
		if(m_pShaderResourceView->CreateSRV((*itr)->GetCurrentSprite().GetPicPath()))
		{
			//计算图片大小
			XMFLOAT2 picSize = m_pShaderResourceView->CalPicSize((*itr)->GetCurrentSprite().GetPicPath());
			//载入对象
			(*itr)->LoadMe(Point(picSize.x,picSize.y));
		}
	}

	LGCenter::Instance()->GetCurrentScene()->DirtyObject();
	LGCenter::Instance()->GetCurrentScene()->hadLoadAll();
	
}

void DXCenter::DXRender()
{
	m_pContext->IASetInputLayout(m_pInputLayout->GetIL(L"IL1"));
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->VSSetShader(m_pVertexShader->GetVS(L"VS1"));
	m_pContext->PSSetShader(m_pPixelShader->GetPS(L"PS1"));
	m_pContext->PSSetSamplers(m_pSamplerState->GetSampler(L"SS1"));

	Scene* currentScene = LGCenter::Instance()->GetCurrentScene();
	CHECK_TO_RETURN(currentScene);

	//将当前场景的游戏对象绘制
	vector<Object*> currentObjVec = currentScene->GetAllDirtyObject();
	for (vector<Object*>::const_iterator itrObj = currentObjVec.begin(); itrObj != currentObjVec.end(); ++itrObj)
	{
		std::vector<LGRect> RectVec = (*itrObj)->GetRectDirty();

		for (std::vector<LGRect>::const_iterator itrRect = RectVec.begin(); 
			itrRect != RectVec.end(); ++itrRect)
		{
			Sprite const& currentSprite = (*itrObj)->GetCurrentSprite();
			wstring currentPath = currentSprite.GetPicPath();

			//更新图片（本质是设置着色器资源视图）
			m_pContext->PSSetShaderResources(m_pShaderResourceView->GetSRV(currentPath));

			//更新精灵位置和动画（本质是更新顶点位置和UV坐标）
			m_pContext->FreshPic<VertexPos>(m_pVertexBuffer->GetVB(L"VB1"), 
				currentSprite.GetPicSizeWidth(), currentSprite.GetPicSizeHeight(),
				currentSprite.GetCurrentRow(), currentSprite.GetCurrentCol(), 
				(*itrObj)->GetSpriteRect(),(*itrRect));

			//设置顶点
			m_pContext->IASetVertexBuffers<VertexPos>(m_pVertexBuffer->GetVB(L"VB1"));

			//更新模型-世界-视图矩阵
			XMMATRIX mvp = m_pVPMatrix->CreateMVP(L"VP1",
				XMFLOAT2((*itrRect).GetX(),(*itrRect).GetY()));
			m_pContext->UpdateSubresource(m_pConstBuffer->GetCB(L"CB1") ,&mvp);
			m_pContext->VSSetConstantBuffers(m_pConstBuffer->GetCB(L"CB1"));

			//绘制当前对象
			m_pContext->Draw();
		}

	}

	g_pLGCenter->GetCurrentScene()->ClearDirty();
	
	m_pSwapChain->Present(L"SC1");
	
}

HINSTANCE const& DXCenter::GetHInstance() const
{
	return m_hInstance;
}

HWND const& DXCenter::GetHWnd() const
{
	return m_hwnd;
}

void DXCenter::InputUpdate()
{
	m_pDXInput->BeginInputMsg();

	unsigned char DXKeyCode[] = {DIK_UP, DIK_DOWN, DIK_LEFT, DIK_RIGHT,DIK_SPACE};

	for (int i = 0; i != LGInput::E_KeyNum; i++ )
	{
		SYNCKeyBoard(DXKeyCode[i],i);
	}

	m_pDXInput->EndInputMsg();
}


void DXCenter::SYNCKeyBoard(unsigned char DXKeyCode, int LGKeyCode)
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