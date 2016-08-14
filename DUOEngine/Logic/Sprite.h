#pragma once

#include "LGHead.h"
#include "Point.h"

class Sprite
{
public:

	Sprite(std::wstring picPath, int rowNum = 1, int colNum = 1, int setRow = 0, int setCol = 0,	//0是第一行/列
		float setFrameSpeed = 0.6f);
	Sprite();
	~Sprite();
	std::wstring const& GetPicPath() const;
	void SetPicPath(std::wstring val);
	int const& GetRowNum() const;
	void SetRowNum(int val);
	int const& GetColNum() const;
	void SetColNum(int val);
	int const& GetCurrentRow() const;
	void SetCurrentRow(int val);
	int const& GetCurrentCol() const;
	void SetCurrentCol(int val);
	void SetRowAndCol(int row, int col);
	int& HaveCurrentRow();
	int& HaveCurrentCol();
	float const& GetFrameSpeed() const;
	void SetFrameSpeed(float val);
	float const& GetPicSizeWidth() const;
	void SetPicSizeWidth(float val);
	float const& GetPicSizeHeight() const;
	void SetPicSizeHeight(float val);
	void SetPicSize(Point val);
	
private:
	std::wstring m_PicPath;
	int m_RowNum;
	int m_ColNum;
	int m_CurrentRow;
	int m_CurrentCol;
	float m_frameSpeed;
	float m_picSizeWidth;
	float m_picSizeHeight;
};
