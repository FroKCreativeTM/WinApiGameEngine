#include "CRectCollider.h"

CRectCollider::CRectCollider()
{
	m_eColType = CT_RECT;
}

CRectCollider::CRectCollider(const CRectCollider& col) : 
	CCollider(col)
{
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
}

int CRectCollider::Update(float fDeltaTime)
{
	return 0;
}

int CRectCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CRectCollider::Collision(float fDeltaTime)
{
}

void CRectCollider::Render(HDC hDC, float fDeltaTime)
{
}

CRectCollider* CRectCollider::Clone()
{
	return new CRectCollider(*this);
}
