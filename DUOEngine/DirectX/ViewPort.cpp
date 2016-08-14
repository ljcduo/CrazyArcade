#include "ViewPort.h"

using namespace std;

ViewPort::ViewPort() 
{

}

ViewPort::~ViewPort()
{
	Util::MapSecondDelete(m_MapVP);
}

void ViewPort::CreateVP(wstring vpName,int width,int height)
{
	D3D11_VIEWPORT *viewport = new D3D11_VIEWPORT;
	viewport->Width = static_cast<float>(width);
	viewport->Height = static_cast<float>(height);
	viewport->MinDepth = 0.0f;
	viewport->MaxDepth = 1.0f;
	viewport->TopLeftX = 0.0f;
	viewport->TopLeftY = 0.0f;

	m_MapVP.insert(pair<wstring,D3D11_VIEWPORT*>(vpName,viewport));
}

D3D11_VIEWPORT* const& ViewPort::GetVP(std::wstring vpName) const
{
	return m_MapVP.find(vpName)->second;
}