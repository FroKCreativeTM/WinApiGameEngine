#include "CUIButton.h"
#include "../Collider/CRectCollider.h"      // 마우스 충돌을 위한 용도
#include "../Core/CInput.h"                 // 마우스 입력에 대한 처리용도

CUIButton::CUIButton() : 
    m_bEnableCallback(false),
    m_eButtonState(BS_NONE)
{
}

CUIButton::CUIButton(const CUIButton& ref) : 
    CUI(ref),
    m_eButtonState(BS_NONE)
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

    // LBUTTON 클릭을 했는지 판단한다.
    if (m_eButtonState != BS_NONE)
    {
        if (KEYDOWN("MouseLButton"))
        {
            m_eButtonState = BS_CLICK;
            SetImageOffset(m_tSize.x * 2, 0.f);
        }
    }

    // 만약 클릭 후 뗀다면
    if (m_eButtonState == BS_CLICK && KEYUP("MouseLButton"))
    {
        m_eButtonState = BS_MOUSEON;
        SetImageOffset(m_tSize.x, 0.f);
        // 콜백 적용이 되었을때
        if (m_bEnableCallback)
        {
            m_BtnCallback(fDeltaTime);
        }
    }

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
    // 무조건 마우스라는 보장이 없기 때문에 이에 대한 정보를 가져와야한다.
    if (pDst->GetTag() == "Mouse")
    {
        m_eButtonState = BS_MOUSEON;

        // 이미지 offset 변경
        SetImageOffset(m_tSize.x, 0.f);
    }
}

void CUIButton::MouseOut(CCollider* pSrc, CCollider* pDst, float fDeltaTime)
{
    if (pDst->GetTag() == "Mouse")
    {
        m_eButtonState = BS_NONE;
        SetImageOffset(0.f, 0.f);
    }
}
