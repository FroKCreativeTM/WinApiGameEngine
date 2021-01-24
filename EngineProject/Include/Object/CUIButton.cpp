#include "CUIButton.h"
#include "../Collider/CRectCollider.h"      // 마우스 충돌을 위한 용도

CUIButton::CUIButton() : 
    m_bEnableCallback(false)
{
}

CUIButton::CUIButton(const CUIButton& ref) : 
    CUI(ref)
{
    m_bEnableCallback = ref.m_bEnableCallback;
}

CUIButton::~CUIButton()
{
}

bool CUIButton::Init()
{
    CRectCollider* pCollider = AddCollider<CRectCollider>("ButtonBody");
    SAFE_RELEASE(pCollider);

    return true;
}

void CUIButton::Input(float fDeltaTime)
{
    CUI::Input(fDeltaTime);
}

int CUIButton::Update(float fDeltaTime)
{
    CUI::Update(fDeltaTime);
    return 0;
}

int CUIButton::LateUpdate(float fDeltaTime)
{
    CUI::LateUpdate(fDeltaTime);
    return 0;
}

void CUIButton::Collision(float fDeltaTime)
{
    CUI::Collision(fDeltaTime);
}

void CUIButton::Render(HDC hDC, float fDeltaTime)
{
    CUI::Render(hDC, fDeltaTime);
}

CUIButton* CUIButton::Clone()
{
    return new CUIButton(*this);
}

void CUIButton::MouseOn(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
}

void CUIButton::MouseOut(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
}
