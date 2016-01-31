#include "Object.h"
#include "Scene.h"
#include "DUOEngine.h"
#include "PlayScene.h"

int Object::NextID = 0;

Sprite const& Object::GetCurrentSprite() const
{
	return m_currentSprite;
}

void Object::SetCurrentSprite(IN Sprite val)
{
	m_currentSprite = val;
}

Object::Object(std::wstring objName, Sprite currentSprite,int layout, Point pixelPos, 
	int objType /*= 0*/) : 
m_objName(objName),m_currentSprite(currentSprite),m_Layout(layout),
	m_pixelPos(pixelPos),m_ObjectType(objType),m_addToOneSum(0.0f),m_frameIndex(0),m_ID(NextID),
	m_hasInit(false),m_visiable(true)
{
	++NextID;
}

Object::Object()
	:m_addToOneSum(0.0f),m_frameIndex(0),m_ID(NextID),m_hasInit(false),m_visiable(true)
{
	++NextID;
}


int const& Object::GetLayout() const
{
	return m_Layout;
}

void Object::SetLayout(int val)
{
	m_Layout = val;
}

std::wstring const& Object::GetObjName() const
{
	return m_objName;
}

void Object::SetObjName(std::wstring val)
{
	m_objName = val;
}

Object::~Object()
{
	SpreadDirty();
}

Sprite& Object::HavaCurrentSprite()
{
	return m_currentSprite;
}

int Object::GetPixelPosX() const
{
	return m_pixelPos.GetXInt();
}

void Object::SetPixelPosX(float val)
{
	SpreadDirty();// 移动前发出脏源
	m_pixelPos.SetX(val);
	SpreadDirty();//移动后也要发出脏源
}

int Object::GetPixelPosY() const
{
	return m_pixelPos.GetYInt();
}

void Object::SetPixelPosY(float val)
{
	SpreadDirty();// 移动前发出脏源
	m_pixelPos.SetY(val);
	SpreadDirty();//移动后也要发出脏源
}

bool Object::OrderCompare(Object* const& rhs)
{
	if ( (this == NULL) || (rhs == NULL))
		return false;

	if (this->GetLayout() < rhs->GetLayout())
	{
		return true;
	}
	else if (this->GetLayout() > rhs->GetLayout())
	{
		return false;
	}
	else
		return this->GetPixelPosY() > rhs->GetPixelPosY();
}

LGRect const& Object::GetRectCollision() const
{
	return m_RectCollision;
}

int const& Object::GetObjectType() const
{
	return m_ObjectType;
}

void Object::SetObjectType(int val)
{
	m_ObjectType = val;
}

bool Object::HandleMessage(const Telegram& telegram)
{
	return false;
}

void Object::Update(float deltaTime)
{

}

bool Object::UpdateAnimateFrame(float deltaTime,const int* frame /*= NULL*/, int frameCount /*= 0*/)
{
	if (Util::AccumulateToOne(&m_addToOneSum,m_currentSprite.GetFrameSpeed() * deltaTime))
	{
		SpreadDirty();
		if(frame == NULL)
		{
			//默认动画帧事件，Col向后移动
			m_currentSprite.SetCurrentCol(m_currentSprite.GetCurrentCol()+1);
		}
		else
		{
			m_currentSprite.SetCurrentCol(frame[m_frameIndex]);
			if (++m_frameIndex == frameCount)
			{
				m_frameIndex = 0;
				return true;
			}
		}


	}
	return false;
}

void Object::UpdateRectCollision(int offsetX , int offsetY, int offsetWidth, int offsetHeight )
{
	m_RectCollision = LGRect(m_pixelPos.GetX() + offsetX,m_pixelPos.GetY() +offsetY,
		static_cast<float>(Util::MAPPIECEPIX) + offsetWidth,static_cast<float>(Util::MAPPIECEPIX) + offsetHeight);
}

int const& Object::GetObjID() const
{
	return m_ID;
}

std::vector<LGRect> const& Object::GetRectDirty() const
{
	return m_RectDirty;
}

void Object::ReceiveDirty(LGRect val)
{
	for (std::vector<LGRect>::const_iterator itr = m_RectDirty.begin(); itr != m_RectDirty.end(); itr++)
	{
		if(Util::CollisionInsideRect(val,*itr))
		{
			return;
		}
		else if(Util::CollisionInsideRect(*itr,val))
		{
			m_RectDirty.erase(itr);
			m_RectDirty.push_back(val);
			return;
		}

	}

	m_RectDirty.push_back(val);

}

void Object::clearDirty()
{
	m_RectDirty.clear();
}

void Object::SpreadDirty()
{
	UpdateSpriteRect();
	g_pLGCenter->GetCurrentScene()->DirtyScene(m_SpriteRect);
	//SetRectDirty(m_SpriteRect);
	//g_pLGCenter->GetCurrentScene()->InsertDetectDirtyObject(this); //加入脏对象检测集合
}

void Object::LoadMe(Point picSize)
{
	// 设置图片大小（用于渲染）
	HavaCurrentSprite().SetPicSize(picSize);
	// 根据是否可见来设置是否为脏源
	if (GetVisiable())
	{
		SpreadDirty();
	}
}

void Object::UpdateSpriteRect()
{
	m_SpriteRect = LGRect(m_pixelPos.GetX(),m_pixelPos.GetY(),
		m_currentSprite.GetPicSizeWidth() / m_currentSprite.GetColNum(),
		m_currentSprite.GetPicSizeHeight() / m_currentSprite.GetRowNum());
}

LGRect Object::GetSpriteRect()
{
	//UpdateSpriteRect();
	return m_SpriteRect;
}

bool const& Object::GetVisiable() const
{
	return m_visiable;
}

void Object::SetVisiable(bool val)
{
	m_visiable = val;
}

