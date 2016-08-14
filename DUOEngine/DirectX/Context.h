#pragma once

#include "DXHead.h"

#include "PixelShader.h"
#include "VertexShader.h"
#include "InputLayout.h"
#include "ShaderResourceView.h"
#include "SamplerState.h"
#include "VertexBuffer.h"
#include "ConstBuffer.h"
#include "VPMatrix.h"
#include "BlendState.h"
#include "Rect.h"

class Context
{
public:
	Context(ID3D11DeviceContext* pID3DContext);
	~Context();

	void ClearRenderTargetView(ID3D11RenderTargetView* pIRenderTargetView);
	void IASetInputLayout(ID3D11InputLayout* pIInputLayout);
	void IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY);
	void VSSetShader(ID3D11VertexShader* pIVertexShader);
	void PSSetShader(ID3D11PixelShader* pIPixelShader);
	void PSSetSamplers(ID3D11SamplerState* pISamplerState);
	void PSSetShaderResources(ID3D11ShaderResourceView* pIShaderResourceView);
	void UpdateSubresource(ID3D11Buffer* pIBuffer,XMMATRIX* mvp);
	void VSSetConstantBuffers(ID3D11Buffer* pIBuffer);
	void OMSetBlendState(ID3D11BlendState* pIBlendState);
	void Draw();
	
	template<typename VertexType>
	void IASetVertexBuffers(ID3D11Buffer* pIVertexBuffer);

	template<typename VertexType>
	void FreshPic(ID3D11Buffer* pIVertexBuffer, float picWidth, float picHeight, 
		int rowNum, int colNum, int currentRow, int currentCol);
	template<typename VertexType> 
	void FreshPic(ID3D11Buffer* pIVertexBuffer, float picWidth, float picHeight,
		int currentRow, int currentCol,LGRect spriteRect,LGRect dirtyRect);
private:
	ID3D11DeviceContext* m_pID3DContext;
};



//模板的实现要写在头文件
template<typename VertexType>
void Context::IASetVertexBuffers(ID3D11Buffer* pIVertexBuffer)
{
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;
	m_pID3DContext->IASetVertexBuffers( 0, 1, &pIVertexBuffer, &stride, &offset );
}


template<typename VertexType>
void Context::FreshPic(ID3D11Buffer* pIVertexBuffer, float picWidth, float picHeight, 
	int rowNum, int colNum, int currentRow, int currentCol)
{	
	float pieceWidth = picWidth / colNum;
	float pieceHeight = picHeight / rowNum;

	float pieceUWidth = static_cast<float>(1) / colNum;
	float pieceVHeight = static_cast<float>(1) / rowNum;

	XMFLOAT2 uvLeftTop = XMFLOAT2(pieceUWidth * currentCol, pieceVHeight * currentRow);
	XMFLOAT2 uvRightBottom = XMFLOAT2(uvLeftTop.x + pieceUWidth , uvLeftTop.y + pieceVHeight);

	//更新顶点缓存的UV坐标
	D3D11_MAPPED_SUBRESOURCE mapResource;
	HRESULT d3dResult = m_pID3DContext->Map( pIVertexBuffer, 0, 
		D3D11_MAP_WRITE_DISCARD, 0, &mapResource );

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( L"精灵动态缓存map映射失败！" );
		assert(false);
	}

	VertexType *spritePtr = ( VertexType* )mapResource.pData;

	//顶点位置坐标系的原点在左下角
	spritePtr[0].pos = XMFLOAT3(pieceWidth,pieceHeight,1.0f);
	spritePtr[1].pos = XMFLOAT3(pieceWidth,0,1.0f);
	spritePtr[2].pos = XMFLOAT3(0,0,1.0f);
	spritePtr[3].pos = XMFLOAT3(0,0,1.0f);
	spritePtr[4].pos = XMFLOAT3(0,pieceHeight,1.0f);
	spritePtr[5].pos = XMFLOAT3(pieceWidth,pieceHeight,1.0f);

	//uv坐标系的原点在左上角
	spritePtr[0].tex0 = XMFLOAT2( uvRightBottom.x, uvLeftTop.y );
	spritePtr[1].tex0 = XMFLOAT2( uvRightBottom.x, uvRightBottom.y );
	spritePtr[2].tex0 = XMFLOAT2( uvLeftTop.x, uvRightBottom.y );
	spritePtr[3].tex0 = XMFLOAT2( uvLeftTop.x, uvRightBottom.y );
	spritePtr[4].tex0 = XMFLOAT2( uvLeftTop.x, uvLeftTop.y );
	spritePtr[5].tex0 = XMFLOAT2( uvRightBottom.x, uvLeftTop.y );

	float halfWidth = static_cast<float>(picWidth) / 2.0f;
	float halfHeight = static_cast<float>(picHeight) / 2.0f;

	m_pID3DContext->Unmap( pIVertexBuffer, 0 );
}

template<typename VertexType>
void Context::FreshPic(ID3D11Buffer* pIVertexBuffer, float picWidth, float picHeight, 
	int currentRow, int currentCol,LGRect spriteRect,LGRect dirtyRect)
{	
	float pieceWidth = dirtyRect.GetWidth();
	float pieceHeight = dirtyRect.GetHeight();

	float pieceUWidth = pieceWidth / picWidth;
	float pieceVHeight = pieceHeight / picHeight;
	
	XMFLOAT2 uvLeftTop = XMFLOAT2( (spriteRect.GetWidth() * currentCol + dirtyRect.GetX() - spriteRect.GetX()) / picWidth,
	( (spriteRect.GetHeight() * (currentRow+1) - ( dirtyRect.GetY() + dirtyRect.GetHeight() - spriteRect.GetY()) ) ) / picHeight);
	XMFLOAT2 uvRightBottom = XMFLOAT2(uvLeftTop.x + pieceUWidth , uvLeftTop.y + pieceVHeight);
	
	//更新顶点缓存的UV坐标
	D3D11_MAPPED_SUBRESOURCE mapResource;
	HRESULT d3dResult = m_pID3DContext->Map( pIVertexBuffer, 0, 
		D3D11_MAP_WRITE_DISCARD, 0, &mapResource);

	if( FAILED( d3dResult ) )
	{
		DXTRACE_MSG( "精灵动态缓存map映射失败！" );
		assert(false);
	}

	VertexType *spritePtr = ( VertexType* )mapResource.pData;

	//顶点位置坐标系的原点在左下角
	spritePtr[0].pos = XMFLOAT3(pieceWidth,pieceHeight,1.0f);
	spritePtr[1].pos = XMFLOAT3(pieceWidth,0,1.0f);
	spritePtr[2].pos = XMFLOAT3(0,0,1.0f);
	spritePtr[3].pos = XMFLOAT3(0,0,1.0f);
	spritePtr[4].pos = XMFLOAT3(0,pieceHeight,1.0f);
	spritePtr[5].pos = XMFLOAT3(pieceWidth,pieceHeight,1.0f);

	//uv坐标系的原点在左上角
	spritePtr[0].tex0 = XMFLOAT2( uvRightBottom.x, uvLeftTop.y );
	spritePtr[1].tex0 = XMFLOAT2( uvRightBottom.x, uvRightBottom.y );
	spritePtr[2].tex0 = XMFLOAT2( uvLeftTop.x, uvRightBottom.y );
	spritePtr[3].tex0 = XMFLOAT2( uvLeftTop.x, uvRightBottom.y );
	spritePtr[4].tex0 = XMFLOAT2( uvLeftTop.x, uvLeftTop.y );
	spritePtr[5].tex0 = XMFLOAT2( uvRightBottom.x, uvLeftTop.y );

	m_pID3DContext->Unmap( pIVertexBuffer, 0 );
}