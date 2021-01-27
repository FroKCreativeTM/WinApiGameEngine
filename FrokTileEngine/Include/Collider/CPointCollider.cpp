#include "CPointCollider.h"
#include "../Object/CObj.h"
#include "CSphereCollider.h"
#include "CPixelCollider.h"
#include "CRectCollider.h"

CPointCollider::CPointCollider()
{
	m_eColType = CT_POINT;
}

CPointCollider::CPointCollider(const CPointCollider& col) : 
	CCollider(col)
{
	m_tDist = col.m_tDist;
}

CPointCollider::~CPointCollider()
{
}

bool CPointCollider::Init()
{
	return true;
}

void CPointCollider::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CPointCollider::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);
	return 0;
}

int CPointCollider::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();
	m_tPos.x = tPos.x + m_tDist.x;
	m_tPos.y = tPos.y + m_tDist.y;

	return 0;
}

bool CPointCollider::Collision(CCollider* pDst)
{
	switch (pDst->GetColliderType())
	{
	case CT_RECT:
		return CollisionRectToPoint(((CRectCollider*)pDst)->GetWorldInfo(), m_tPos);
	case CT_SPHERE:
		return CollisionSphereToPoint(((CSphereCollider*)pDst)->GetWorldInfo(), m_tPos);
	case CT_PIXEL:
		return CollisionPixelToPoint(((CPixelCollider*)pDst)->GetPixel(),
			((CPixelCollider*)pDst)->GetWidth(), ((CPixelCollider*)pDst)->GetHeight(), m_tPos);
	}
	return false;
}

void CPointCollider::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CPointCollider* CPointCollider::Clone()
{
	return new CPointCollider(*this);
}

void CPointCollider::Save(FILE* pFile)
{
}

void CPointCollider::Load(FILE* pFile)
{
}
