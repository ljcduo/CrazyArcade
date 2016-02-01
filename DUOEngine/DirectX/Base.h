//DX11框架，搭建基本设施


#pragma once

#include "DXHead.h"
#include "SwapChain.h"
#include "RenderTargetView.h"

class Dx11DemoBase
{
    public:
        Dx11DemoBase();
        virtual ~Dx11DemoBase( );

        bool Initialize( HINSTANCE hInstance, HWND hwnd );
        void Shutdown();

        virtual bool LoadContent();
        virtual void UnloadContent();

        virtual void DXUpdate( float dt ) = 0;
        virtual void DXRender() = 0;

    protected:
        HINSTANCE m_hInstance;
        HWND m_hwnd;

        D3D_DRIVER_TYPE m_driverType;
        D3D_FEATURE_LEVEL m_featureLevel;

		ID3D11Device *m_pID3DDevice;
        ID3D11DeviceContext* m_pID3DContext;

        SwapChain* m_pSwapChain;
        RenderTargetView* m_pRenderTargetView;


};
