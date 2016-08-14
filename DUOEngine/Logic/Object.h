#pragma once

#include "Sprite.h"
#include "Telegram.h"
#include "Rect.h"

class Object
{
public:
	Object(std::wstring objName, Sprite currentSprite,int layout, Point pixelPos, 
		int objType = 0);
	Object();
	virtual ~Object();

	void LoadMe(Point picSize);

	Sprite const& GetCurrentSprite() const;
	int const& GetLayout() const;
	std::wstring const& GetObjName() const;
	int GetPixelPosX() const;
	int GetPixelPosY() const;
	int const& GetObjID() const;
	bool const& GetVisiable() const;
	LGRect GetSpriteRect();
	LGRect const& GetRectCollision() const;
	int const& GetObjectType() const;

	void SetCurrentSprite(IN Sprite val);
	void SetLayout(int val);
	void SetObjName(std::wstring val);
	void SetPixelPosX(float val);
	void SetPixelPosY(float val);
	void SetVisiable(bool val);
	void SetObjectType(int val);
	Sprite& HavaCurrentSprite();

	virtual bool HandleMessage(const Telegram& telegram);

	bool OrderCompare(Object* const& rhs);

	
	virtual void Update(float deltaTime);
	virtual bool UpdateAnimateFrame(float deltaTime, const int* frame = NULL, int frameCount = 0);	//当动画循环一遍，返回true
	virtual void UpdateRectCollision(int offsetX = 0, int offsetY = 0, int offsetWidth = 0, int offsetHeight = 0);
	void UpdateSpriteRect();

	//-------------------------------脏矩形算法-begin------------------------------

	void SpreadDirty(); //发出脏源（污染）
	void ReceiveDirty(LGRect val);//接收局部脏矩形部位（被污染）
	void clearDirty(); //渲染完毕可以清除脏矩形
	std::vector<LGRect> const& GetRectDirty() const; //取得该对象脏的局部矩形部位

	//-------------------------------脏矩形算法-end------------------------------
protected:
	Sprite m_currentSprite;
	int m_Layout;
	std::wstring m_objName;
	Point m_pixelPos;
	LGRect m_RectCollision;
	int m_ObjectType;
	static int NextID;
	int m_ID;
	std::vector<LGRect> m_RectDirty;
	LGRect m_SpriteRect;
	bool m_visiable;
private:
	float m_addToOneSum;
	int m_frameIndex;
	bool m_hasInit;
};