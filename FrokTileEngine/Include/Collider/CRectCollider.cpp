#include "CRectCollider.h"
#include "../Object/CObj.h"
#include "CSphereCollider.h"
#include "CPixelCollider.h"
#include "CPointCollider.h"
#include "../Core/CCamera.h"

CRectCollider::CRectCollider()
{
	m_eColType = CT_RECT;
}

CRectCollider::CRectCollider(const CRectCollider& col) : 
	CCollider(col)
{
	m_tInfo = col.m_tInfo;
}

CRectCollider::~CRectCollider()
{
}

bool CRectCollider::Init()
{
	return true;
}

void CRectCollider::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CRectCollider::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CRectCollider::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	// 위치 정보 뽑아온다.
	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.left = tPos.x + m_tInfo.left;
	m_tWorldInfo.top = tPos.y + m_tInfo.top;
	m_tWorldInfo.right = tPos.x + m_tInfo.right;
	m_tWorldInfo.bottom = tPos.y + m_tInfo.bottom;

	return 0;
}

bool CRectCollider::Collision(CCollider* pDst)
{
	switch (pDst->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo, ((CRectCollider*)pDst)->GetWorldInfo());
	case CT_SPHERE:
		return CollisionRectToSphere(m_tWorldInfo, ((CSphereCollider*)pDst)->GetWorldInfo());
	case CT_PIXEL:
		return CollisionRectToPixel(m_tWorldInfo, ((CPixelCollider*)pDst)->GetPixel(), 
			((CPixelCollider*)pDst)->GetWidth(), ((CPixelCollider*)pDst)->GetHeight());
	case CT_POINT:
		return CollisionRectToPoint(m_tWorldInfo, ((CPointCollider*)pDst)->GetPoint());
	}
	return false;
}

void CRectCollider::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
#ifdef _DEBUG
	/* 컬링 작업용! (화면 밖으로 나간 오브젝트는 걸러내자! */

	POSITION tCamPos = GET_SINGLE(CCamera)->GetPos();

	RECTANGLE tRect = m_tWorldInfo;
	tRect.left -= tCamPos.x;
	tRect.right -= tCamPos.x;
	tRect.top -= tCamPos.y;
	tRect.bottom -= tCamPos.y;

	MoveToEx(hDC, tRect.left, tRect.top, nullptr);
	LineTo(hDC, tRect.right, tRect.top);
	LineTo(hDC, tRect.right, tRect.bottom);
	LineTo(hDC, tRect.left, tRect.bottom);
	LineTo(hDC, tRect.left, tRect.top);
#endif // DEBUG
}

CRectCollider* CRectCollider::Clone()
{
	return new CRectCollider(*this);
}

void CRectCollider::SetRect(
	float left, float top, float right, float bottom)
{
	m_tInfo.left = left;
	m_tInfo.top = top;
	m_tInfo.right = right;
	m_tInfo.bottom = bottom; 
}
