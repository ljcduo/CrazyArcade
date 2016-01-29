#include "Sprite.h"


Sprite::~Sprite()
{

}

std::wstring const& Sprite::GetPicPath() const
{
	return m_PicPath;
}

void Sprite::SetPicPath(std::wstring val)
{
	m_PicPath = val;
}



Sprite::Sprite(std::wstring picPath, int rowNum /*= 1*/, int colNum /*= 1*/, int setRow /*= 0*/, int setCol /*= 0*/,
	float setFrameSpeed /*= 0.6*/)
	:m_PicPath(picPath),m_RowNum(rowNum),m_ColNum(colNum),
	m_CurrentRow(setRow),m_CurrentCol(setCol), m_frameSpeed(setFrameSpeed)
{
	
}

Sprite::Sprite()
{

}

int const& Sprite::GetRowNum() const
{
	return m_RowNum;
}

void Sprite::SetRowNum(int val)
{
	m_RowNum = val;
}

int const& Sprite::GetColNum() const
{
	return m_ColNum;
}

void Sprite::SetColNum(int val)
{
	m_ColNum = val;
}

int const& Sprite::GetCurrentRow() const
{
	return m_CurrentRow;
}

void Sprite::SetCurrentRow(int val)
{
	if (m_CurrentRow >= m_RowNum)
	{
		m_CurrentRow = 0;
	}
	else
	{
		m_CurrentRow = val;
	}
}

int const& Sprite::GetCurrentCol() const
{
	return m_CurrentCol;
}

void Sprite::SetCurrentCol(int val)
{
	if (m_CurrentCol >= m_ColNum)
	{
		m_CurrentCol = 0;
	}
	else
	{
		m_CurrentCol = val;
	}
}

void Sprite::SetRowAndCol(int row, int col)
{
	SetCurrentRow(row);
	SetCurrentCol(col);
}



float const& Sprite::GetFrameSpeed() const
{
	return m_frameSpeed;
}

void Sprite::SetFrameSpeed(float val)
{
	m_frameSpeed = val;
}

int& Sprite::HaveCurrentRow() 
{
	return m_CurrentRow;
}

int& Sprite::HaveCurrentCol() 
{
	return m_CurrentCol;
}

float const& Sprite::GetPicSizeWidth() const
{
	return m_picSizeWidth;
}

void Sprite::SetPicSizeWidth(float val)
{
	m_picSizeWidth = val;
}

float const& Sprite::GetPicSizeHeight() const
{
	return m_picSizeHeight;
}

void Sprite::SetPicSizeHeight(float val)
{
	m_picSizeHeight = val;
}

void Sprite::SetPicSize(Point val)
{
	m_picSizeWidth = val.GetX();
	m_picSizeHeight = val.GetY();
}

