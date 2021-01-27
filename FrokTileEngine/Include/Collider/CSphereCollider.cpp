#include "CSphereCollider.h"
#include "../Object/CObj.h"
#include "CRectCollider.h"
#include "CPixelCollider.h"
#include "CPointCollider.h"

bool CSphereCollider::Init()
{
    return true;
}

void CSphereCollider::Input(float fDeltaTime)
{
    CCollider::Input(fDeltaTime);
}

int CSphereCollider::Update(float fDeltaTime)
{
    CCollider::Update(fDeltaTime);
    return 0;
}

int CSphereCollider::LateUpdate(float fDeltaTime)
{
    CCollider::LateUpdate(fDeltaTime);


    // 위치 정보 뽑아온다.
    POSITION tPos = m_pObj->GetPos();
    m_tWorldInfo.tCenter = tPos + m_tInfo.tCenter;
    m_tWorldInfo.fRadius = m_tInfo.fRadius;

    return 0;
}

bool CSphereCollider::Collision(CCollider* pDst)
{
    switch (pDst->GetColliderType())
    {
    case CT_SPHERE:
        return CollisionSphereToSphere(m_tWorldInfo, ((CSphereCollider*)pDst)->GetWorldInfo());
    case CT_RECT:
        return CollisionRectToSphere(((CRectCollider*)pDst)->GetWorldInfo(), m_tWorldInfo);
    case CT_POINT:
        return CollisionSphereToPoint(m_tWorldInfo, ((CPointCollider*)pDst)->GetPoint());
    }

    return false;
}

void CSphereCollider::Render(HDC hDC, float fDeltaTime)
{
    CCollider::Render(hDC, fDeltaTime);
}

CSphereCollider* CSphereCollider::Clone()
{
    return new CSphereCollider(*this);
}

void CSphereCollider::Save(FILE* pFile)
{
}

void CSphereCollider::Load(FILE* pFile)
{
}

CSphereCollider::CSphereCollider()
{
    m_eColType = CT_SPHERE;
}

CSphereCollider::CSphereCollider(const CSphereCollider& col) : 
    CCollider(col)
{
    m_tInfo = col.m_tInfo;
}

CSphereCollider::~CSphereCollider()
{
}
