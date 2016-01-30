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

	Sprite const& GetCurrentSprite() const;
	Sprite& HavaCurrentSprite();
	void SetCurrentSprite(IN Sprite val);

	Point const& GetClientPos() const;
	void SetClientPos(Point val);
	int const& GetLayout() const;
	void SetLayout(int val);
	std::wstring const& GetObjName() const;
	void SetObjName(std::wstring val);
	int GetPixelPosX() const;
	void SetPixelPosX(float val);
	int GetPixelPosY() const;
	void SetPixelPosY(float val);
	int const& GetObjID() const;
	bool const& GetVisiable() const;
	void SetVisiable(bool val);
	bool const& GetDirty() const;
	LGRect GetSpriteRect();
	bool const& GetHasInit() const;
	void SetHasInit(bool val);

	virtual bool HandleMessage(const Telegram& telegram);

	bool OrderCompare(Object* const& rhs);
	LGRect const& GetRectCollision() const;
	int const& GetObjectType() const;
	void SetObjectType(int val);
	virtual void Update(float deltaTime);
	virtual bool UpdateAnimateFrame(float deltaTime, const int* frame = NULL, int frameCount = 0);	//当动画循环一遍，返回true
	void UpdateRectCollision(int offsetX = 0, int offsetY = 0, int offsetWidth = 0, int offsetHeight = 0);
	void UpdateSpriteRect();

	void SetDirty(bool val); //true为设置该精灵矩形全脏，false清空该精灵的所有脏矩形
	std::vector<LGRect> const& GetRectDirty() const;
	void SetRectDirty(LGRect val);//设置加入精灵自身的脏矩形，不加入脏矩形检测集合
	void SetDirtySource(bool setRectDirty = true); //设置该精灵自身为脏矩形，不将该精灵的矩形加入脏矩形检测集合
protected:
	//原点在左下角
	int m_mapPosX;
	int m_mapPosY;

	Sprite m_currentSprite;
	int m_Layout;
	std::wstring m_objName;
	Point m_pixelPos;
	LGRect m_RectCollision;
	int m_ObjectType;
	static int NextID;
	int m_ID;
	bool m_dirty;
	std::vector<LGRect> m_RectDirty;
	LGRect m_SpriteRect;
	bool m_visiable;
private:
	float m_addToOneSum;
	int m_frameIndex;
	bool m_hasInit;
};