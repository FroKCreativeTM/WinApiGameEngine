#include "CCollider.h"
#include "../Object/CObj.h"

bool CCollider::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dst)
{
	if (src.left > dst.right)
	{
		return false;
	}
	else if (src.right < dst.left)
	{
		return false;
	}
	else if (src.top > dst.bottom)
	{
		return false;
	}
	else if (src.bottom < dst.top)
	{
		return false;
	}
	return true;
}

CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider& col)
{
	*this = col;
}

CCollider::~CCollider()
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter)
	{
		// 날 가진 것을 다 지워
		(*iter)->EraseCollsionList(this);
	}
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDst)
{
	return false;
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}